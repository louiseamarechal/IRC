#include "Server.hpp"
#include "User.hpp"

int main( void ) {

    Server  Server;

    while (true) {

        sockaddr_in client_address;

        socklen_t client_address_size = sizeof(client_address);
        
        int client_socket = accept(Server._serverSocket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket < 0) {
            std::cerr << "Failed to accept incoming connection" << std::endl;
            continue;
        }
        std::cout<< "client socket = " << client_socket<<std::endl;

        fds[0].fd = client_socket;
        fds[0].events = POLLIN; 

        int nready = poll(fds, 2, 100);
        char buffer[1024];

        char buffer2[3];
        send(client_socket, "001 coucou :Welcome to the JLA.com Network, jbouyer \r\n", 60, 0);

        if(fds[0].revents & POLLIN) {
            std::cout<<"coucou\n";
        std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl; 
        std::cout<<buffer<<std::endl; 
        }

        std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
         std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
         std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
        std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
        std::cout<<recv(client_socket, buffer, 1024, 0)<<std::endl;
        std::cout<<buffer<<std::endl;

    }
    return 0;


}