#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include <sys/epoll.h>

int    acceptconnexion()
{
    sockaddr_in clientAddress;
    int   clientFd;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int client_fd;

    client_fd = accept(serverFd, (sockaddr*)&clientAddress, &clientAddressSize);
    if (clientFd < 0)
        sendError("Failed to accept incoming connection");
    else
    {
        std::cout<< "Accepted connection: fd #" << clientFd <<std::endl;
        addUser(clientFd);
    }
    return(client_fd);
}

int    Server::runServer( void ) 
{
    char        buffer[1024];
    int         nBytes;
    int         event_count;
    int         client_fd;
    int         serverFd = createSocket();
    sockaddr_in serverAddress = bindSocket( serverFd ); //on init le server.
    // Listen for incoming connections
    int listenResult = listen(serverFd, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;
    
    int epoll_fd = epoll_create1(0); // on init le epoll_fd.

	if (epoll_fd == -1) 
    {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverFd, &event)) //on ajoute le fd du server a la liste de poll;
    {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}
	while (1) 
    {
		std::cout << "\nPolling for input..."<<std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << event_count << " ready events" << std::endl;
		for (i = 0; i < event_count; i++)
         {
			std::cout<< "Reading file descriptor" << events[i].data.fd << std::endl;
            if (events[i].data.fd == serverFd)
            {
                int client_fd = acceptconnexion(events[i].data.fd,);
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverFd, &event)) //on ajoute le fd du nouvequ client a la liste de poll;
                {
                    fprintf(stderr, "Failed to add new file descriptor to epoll\n");
                    close(epoll_fd);
                    return 1;
                }
            }
			nBytes = recv(events[i].data.fd, buffer, sizof(buffer), 0);
            if (nBytes <= 0)
                    {
                        removeUser(clientSocket);
                        continue;
                    }
                    if (nBytes > 0)
                    {
                        buffer[nBytes] = '\0';
                        std::cout << "Buffer Server = " << buffer << std::endl;
                        _userMap[clientSocket]->handleCommand(buffer);
                        // memset(buffer, 0, sizeof(buffer));
                    }
		}
	}
    return (0);
}