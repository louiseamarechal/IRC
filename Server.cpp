#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"

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
    _commandMap["NICK"] = &setNick;
    // _commandMap['USER'] = &setUser;
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
    
    _userMap.erase(_fds[i].fd);
    _fds[i] = _fds[_nbUsers -  1];

    _nbUsers--;
}

void    Server::addUser( int fd) {
    
    if ( _nbUsers < _maxUsers )
    {
        User  newUser = User(fd, *this);
        _userMap.insert( std::pair<int, User*>( fd, &newUser ) );
        _nbUsers++;
    }
    else
        std::cout << "Too many users ! " << std::endl;
}

int     Server::createSocket( void ) {

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

sockaddr_in Server::bindSocket( int serverSocket ) {

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

int    Server::runServer( void ) {

    sockaddr_in clientAddress;
    int         clientSocket;
    int         pollCount;
    int         senderFd;
    int         destFd;
    char        buffer[1024];
    int         nBytes;
    int         serverSocket = createSocket();
    sockaddr_in serverAddress = bindSocket( serverSocket );
    
    
    // Listen for incoming connections
    int listenResult = listen(serverSocket, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;

    // Accept and handle connections
    while ( _nbUsers < _maxUsers) {

        socklen_t clientAddressSize = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressSize);
        
        if (clientSocket < 0)
            sendError("Failed to accept incoming connection");
        else
        {
            std::cout<< "Accepted connection: fd #" << clientSocket <<std::endl;
            _fds[_nbUsers].fd = clientSocket;
            _fds[_nbUsers].events = POLLIN;
            addUser(clientSocket);
        }

        pollCount = poll(_fds, _nbUsers, 700);

        if ( pollCount <= 0 ) {

            if ( pollCount < 0 )
                sendError("Poll error !");
            else if ( pollCount == 0 )
                sendError("Times up");
        }
        else
            std::cout << "Poll is a success !" << std::endl;

        for ( int i = 0; i < _nbUsers; i++ ) { // send a message to all people connected to the server

            if ( _fds[i].revents & POLLIN ) { // on a des donnees a lire

                nBytes = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
                senderFd = _fds[i].fd;
                // _userMap[clientSocket].handleBuffer(buffer);

                if (nBytes <= 0) {

                    sendError("Recv Error");
                    close(_fds[i].fd);
                    // removeUser(i);
                }
                else {
                    for( int j = 0; j < _nbUsers; j++ ) {
                        
                        destFd = _fds[j].fd;

                        if (destFd != serverSocket && destFd != senderFd) {
                            if (send(destFd, buffer, nBytes, 0) == -1) {
                                    sendError("Send Error");
                                }
                                // recv(destFd, buffer, nBytes, 0);
                            }
                        }
                    // // handle the information
                    // read(_fds[i].fd, buffer, 100);
                    // send(_fds[i].fd, buffer, 100, 0);
                }
            }
        }
    }
    return (0);
}

