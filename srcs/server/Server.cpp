#include "Server.hpp"
#include <algorithm>
#include "user/User.hpp"
#include "../includes/utils.hpp"
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event


/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Server::Server( void ) : _port(0),
                        _version("2.0"),
                        _serverName("JLA.irc.com"),
                        _password(""),
                        _creationDate("Wed Feb 8 15:53:25 2023"),
                        _nbUsers(0),
                        _maxUsers(10)
{
    _userMap = std::map<int, User*>();
    _commandMap = std::map<std::string, void (*)(std::string, User &)>();
    _nickList = std::vector<std::string>();

    for (int i = 0; i < 200; i++) {
        _fds[i].fd = -1;
    }
    
    _commandMap["NICK"] = &setNick;
    _commandMap["USER"] = &setUser;
    _commandMap["USERHOST"] = &setUser;
    _commandMap["MOTD"] = &motd;
    // _commandMap['JOIN'] = &joinChannel;
    // _commandMap['PASS'] = &checkPass;
    // _commandMap['PRIVMSG'] = &sendPrivMsg;
    return ;
}

Server::~Server( void ) { return ; }

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

int                         Server::getPort() const { return (_port); }
std::string                 Server::getVersion() const { return (_version); }

int                         Server::getNbUsers() const { return (_nbUsers); }
int                         Server::getMaxUsers() const { return (_maxUsers); }

std::string                 Server::getServerName() const { return (_serverName); }

std::string                 Server::getPassword() const { return (_password); }

std::string                 Server::getCreationDate( void ) const { return (_creationDate); }

std::vector<std::string>    Server::getNickList() const { return (_nickList); }

std::map<std::string, void (*)(std::string params, User &user)>    Server::getCommandMap(void)   const { return (_commandMap);}

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

void    Server::setPort( int port ) { _port = port; }

void    Server::setPassword( std::string password ) { _password = password; }

void    Server::setNickList(std::string nick)
{
    _nickList.push_back(nick);
}

void   Server::removeNickList(std::string oldNick)
{
    std::vector<std::string>::iterator it = std::find(_nickList.begin(), _nickList.end(), oldNick);
    if ( it != _nickList.end())
         _nickList.erase(it);
    else 
    {
        std::cout<<" remove old nickname failed" << std::endl;
    }
}

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/
 
void    Server::removeUser( int i ) { 
    //ICI FAIRE BLOC TRY AND CATCH pourjeter une exception si on trouve pas le fd dans la mapde user utiliser Map.at() pour etre sure qu ca existe et que ca cree pas un truc random u'on supprime apres.
        delete _userMap[_fds[i].fd];
    _fds[i] = _fds[_nbUsers -  1];

    _nbUsers--;
}

// PROPOSITON DE LEA :
// void Server::removeUser(int clientFd) {
//     // Trouver l'identifiant du client dans la table de hachage
//     auto userIter = _userMap.find(clientFd);
//     if (userIter == _userMap.end())
//         return;

//     // Supprimer l'entrée associée à ce client dans la table de hachage
//     _userMap.erase(userIter);

//     // Réduire le compteur de clients connectés
//     _nbUsers--;

//     // Fermer la socket associée au client déconnecté
//     close(clientFd);

//     // Mettre à jour la liste des descripteurs de fichiers pollfd
//     for (int i = 0; i < _nbUsers; i++) {
//         if (_fds[i].fd == clientFd) {
//             for (int j = i; j < _nbUsers - 1; j++)
//                 _fds[j] = _fds[j + 1];
//             break;
//         }
//     }
// }

void    Server::addUser( int fd) 
{  
    if ( _nbUsers < _maxUsers && _userMap[fd] == NULL)
    {
        User  *newUser = new User(fd, this);
        _userMap[fd] = newUser;
        _nbUsers++;
    }
    else
        std::cout << "Too many users ! " << std::endl;
}

int     Server::createSocket( void )
{
    int enable = 1;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
        sendError("Failed to create socket");
    else
        std::cout << "Socket created !" << std::endl;
   
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    
    fcntl(serverSocket, F_GETFL, O_NONBLOCK);
    signal(SIGINT, sigintHandler);

    return ( serverSocket );
}

sockaddr_in Server::bindSocket( int serverSocket ) 
{
    sockaddr_in serverAddress;
    int         bindResult;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    bindResult = bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    
    if (bindResult < 0) 
    {
        sendError("Failed to bind socket to port");
        throw std::exception();
    }
    else
        std::cout << "Success, socket binded !" << std::endl;

    return ( serverAddress );
} 

int    Server::acceptconnexion(int server_fd)
{
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int client_fd;

    client_fd = accept(server_fd, (sockaddr*)&clientAddress, &clientAddressSize);
    if (client_fd < 0)
        sendError("Failed to accept incoming connection");
    else
    {
        std::cout<< "Accepted connection: fd #" << client_fd <<std::endl;
        addUser(client_fd);
    }
    return(client_fd);
}

static void    add_fd_to_poll(int epoll_fd, int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event)) //on ajoute le fd du server a la liste de poll;
    {
		std::cout<<"Failed to add file descriptor to epoll"<<std::endl;
		close(epoll_fd);
        throw std::exception();
	}
}

static int   init_epoll()
{
    int epoll_fd = epoll_create1(0); // on init le epoll_fd.

    std::cout<<"epoll_fd = "<<epoll_fd<<std::endl;
	if (epoll_fd == -1) 
    {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}
    return (epoll_fd);
}

int    Server::runServer( void ) 
{
    char                        buffer[1024];
    int                         nBytes;
    int                         event_count;
    int                         client_fd;
    std::string                 data;
    std::vector<std::string>    splittedBuffer;

    int         server_fd = createSocket();
    sockaddr_in serverAddress = bindSocket( server_fd ); //on init le server.
    // Listen for incoming connections
    int listenResult = listen(server_fd, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;
    // on init le epoll_fd. 
    int epoll_fd = init_epoll(); 
    add_fd_to_poll(epoll_fd, server_fd); //on ajoute le fd du server a la liste de poll;
    struct epoll_event events[100];   
	while (1) 
    {
		std::cout << "\nPolling for input..."<<std::endl;
		event_count = epoll_wait(epoll_fd, events, 1, -1);
		std::cout << event_count << " ready events" << std::endl;
		for (int i = 0; i < event_count; i++)
         {
			std::cout<< "Reading file descriptor " << events[i].data.fd << std::endl;
			std::cout<< "server fd = " << server_fd << std::endl;
            if (events[i].data.fd == server_fd)
            {
                client_fd = acceptconnexion(server_fd);
                add_fd_to_poll(epoll_fd, client_fd); //on ajoute le fd du nouvequ client a la liste de poll;
            }
            std::memset(buffer, 0, sizeof(buffer));
			nBytes = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
            std::cout << "Buffer Server = " << buffer << std::endl;
            std::cout << "nBytes  = " << nBytes << std::endl;
            if (nBytes <= 0)
            {
                removeUser(events[i].data.fd);
                continue;
            }
            if (nBytes > 0)
            {
                // buffer[nBytes] = '\0';
                data.append(buffer, nBytes); // j'append les buffer a data (poentiellement des reliquas non recus au tour d'avant)
                if (data.find("\r\n") == std::string::npos) // si je trouve pas de \r\n dans le buffer, je quitte la condition pour pouvoir l'append au tour d'apres
                    break;
                std::cout << "Data Server (after append()) = " << data << std::endl;
                splittedBuffer = splitStringSep(data, "\r\n");
                data.clear();
                for (size_t j = 0; j < splittedBuffer.size(); j++)
                {
                    std::cout << "Command send to Handle Commande -- Server : " << splittedBuffer[j] << std::endl;
                    _userMap[events[i].data.fd]->handleCommand(splittedBuffer[j]);
                }
                splittedBuffer.clear();
            }
		}
	}
    return (0);
}
	