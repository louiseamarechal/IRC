#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"

Server::Server( void ) : _port(""), 
                        _serverName(""),
                        _password(""),
                        _nbUsers(0)
{
    return ;
}

Server::~Server( void ) { return ; }

int Server::getPort() const { return (this->_port); }

int Server::getNbUsers() const { return (this->_nbUsers); }

std::string Server::getServerName() const { return (this->_serverName); }

std::string Server::getPassword() const { return (this->_password); }

void    Server::setPort( int port ) { this->_port = port; }

void    Server::setServerName( std::string serverName ) { this->_serverName = serverName; }

void    Server::setPassword( std::string password ) { this->_password = password };

void    Server::setNbUsers( int nbUsers ) { this->_nbUsers += 1; }

int Server::createSocket( void ) {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        sendError("Failed to create socket");
        return 1;
    }
    else
        std::cout << "Socket created !" << std::endl;
   
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    
    // fcntl(serverSocket, F_GETFL, O_NONBLOCK);
    // signal(SIGINT, sigintHandler);

    return ( serverSocket );
}

sockaddr_in Server::bindSocket( int serverSocket ) {

    sockaddr_in serverAddress;
    int         bindResult;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    bindResult = bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    
    if (bindResult < 0) {
        sendError("Failed to bind socket to port");
        return (1);
    }
    else
        std::cout << "Success, socket binded !" << std::endl;

    return ( serverAddress );
} 

void    Server::runServer( void ) {

    int         serverSocket = createSocket();
    sockaddr_in serverAdress = bindSocket( serverSocket );
    

    // Listen for incoming connections
    int listen_result = listen(serverSocket, serverAddress.sin_port);
    if (listen_result < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;

    // Accept and handle connections
     while (true) {

        sockaddr_in clientAddress;
        // struct pollfd fds;

        socklen_t clientAddressSize = sizeof(clientAddress);
        this->_fds[_nbUsers].fd = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressSize);
        
        if (this->_fds[_nbUsers].fd < 0)
            sendError("Failed to accept incoming connection");
        else
        {
            std::cout<< "Accepted connection to fd#" << this->_fds[_nbUsers].fd <<std::endl;
            this->fds[_nbUsers].events = POLLIN; 
            this->_nbUsers ++;
        }

        
        // Server.fds[getNbUsers()].fd = client_socket;

        // int nready = poll(&fds, 1, 100);
        // if (nready < 0)
        //     std::cout << "Poll error" << std::endl;
        // char buffer[1024];

        // send(client_socket, "001 coucou :Welcome to the JLA.com Network, jbouyer \r\n", 60, 0);

        // read(client_socket, buffer, 100);
        // send(client_socket, buffer, 100, 0);
    }
}