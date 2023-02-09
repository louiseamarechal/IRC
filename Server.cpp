#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event


/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Server::Server( void ) : _port(0),
                        _version("2.0"),
                        _serverName("JLA.irc.com"),
                        _password(""),
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
    // _commandMap["USER"] = &setUser;
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

std::vector<std::string>    Server::getNickList() const { return (_nickList); }

std::map<std::string, void (*)(std::string params, User &user)>    Server::getCommandMap(void)   const { return (_commandMap);}

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

void    Server::setPort( int port ) { _port = port; }

void    Server::setPassword( std::string password ) { _password = password; }

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
    
    if (bindResult < 0) {
        sendError("Failed to bind socket to port");
        // return (1);
    }
    else
        std::cout << "Success, socket binded !" << std::endl;

    return ( serverAddress );
} 

static int		epoll_init()
{
	// Create epoll instance
	int epoll_fd = epoll_create1(0);
	if (epoll_fd < 0)
	{
		std::cerr << "epoll_create1 failed\n";
		throw std::exception();
	}

	return epoll_fd;
}

void    Server::acceptconnexion(int serverFd)
{
    sockaddr_in clientAddress;
    int   clientFd;
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientFd = accept(serverFd, (sockaddr*)&clientAddress, &clientAddressSize);
    // std::cout<<"NOUVELE CONNEXION"<<std::endl;
    if (clientFd < 0)
        sendError("Failed to accept incoming connection");
    else
    {
        std::cout<< "Accepted connection: fd #" << clientFd <<std::endl;
        addUser(clientFd);
    }
}
int    Server::runServer( void ) 
{
    // char        buffer[1024];
    // int         nBytes;
    int         serverFd = createSocket();
    sockaddr_in serverAddress = bindSocket( serverFd );
    int epoll_fd = epoll_init();
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverFd, &event))
    {
        std::cout<<"Failed to create epoll file descriptor";
        close(epoll_fd);
        throw std::exception();
    }
    
    // Listen for incoming connections
    int listenResult = listen(serverFd, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;

    for (int i = 0;; i++)
    {
        memset(&event, 0, sizeof(struct epoll_event));
        int event_count = epoll_wait(epoll_fd, &event, 1, -1);
        std::cout << "new event in epoll" << std::endl;
        for (int i = 0; i < event_count; i++)
        {
            if (event.data.fd == serverFd)
			{
    std::cout<<"NOUVELE CONNEXION"<<std::endl;
				// acceptconnexion(serverFd); //check ca
			}
            // else
            // {
            //     nBytes = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
            //     if (nBytes <= 0)
            //     {
            //         removeUser(event.data.fd);
            //         continue;
            //     }
            //     if (nBytes > 0)
            //     {
            //         buffer[nBytes] = '\0';
            //         std::cout << "Buffer Server = " << buffer << std::endl;
            //         _userMap[event.data.fd]->handleCommand(buffer);
            //     }
            }
        }
    }
    // Accept and handle connections
    // while ( true ) 
    // {
    //     socklen_t clientAddressSize = sizeof(clientAddress);
    //     clientSocket = accept(serverFd, (sockaddr*)&clientAddress, &clientAddressSize);
        
    //     if (clientSocket < 0)
    //         sendError("Failed to accept incoming connection");
    //     else
    //     {
    //         std::cout<< "Accepted connection: fd #" << clientSocket <<std::endl;
    //         _fds[_nbUsers].fd = clientSocket;
    //         _fds[_nbUsers].events = POLLIN;
    //         addUser(clientSocket);
    //     }
    //     while ( _nbUsers > 0 )
    //     {
    //         pollCount = poll(_fds, _nbUsers, 700);
    //         if ( pollCount <= 0 ) 
    //         {
    //             if ( pollCount < 0 )
    //                 sendError("Poll error !");
    //             // else if ( pollCount == 0 )
    //             //     sendError("Times up");
    //         } 
    //         else
    //             std::cout << "Poll is a success !" << std::endl;
    //         for ( int i = 0; i <= _nbUsers; i++ ) 
    //         {
    //             if ( _fds[i].revents & POLLIN ) 
    //             { // on a des donnees a lire
    //                 nBytes = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
    //                 if (nBytes <= 0)
    //                 {
    //                     removeUser(clientSocket);
    //                     continue;
    //                 }
    //                 if (nBytes > 0)
    //                 {
    //                     buffer[nBytes] = '\0';
    //                     std::cout << "Buffer Server = " << buffer << std::endl;
    //                     // std::cout << "i = " << i << std::endl;
    //                     _userMap[clientSocket]->handleCommand(buffer);
    //                     // memset(buffer, 0, sizeof(buffer));
    //                 }
    //             }
    //         }
    //     }
    // }
    return (0);
}

