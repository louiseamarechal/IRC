#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"

Server::Server( void ) {

    int enable = 1;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (_serverSocket < 0) {
        errorMessage("Failed to create Socket");
        return ;
    }

    setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    fcntl(_serverSocket, F_GETFL, O_NONBLOCK);
    signal(SIGINT, sigintHandler);

    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(6667);
    _serverAddress.sin_addr.s_addr = INADDR_ANY; // htonl(INADDR_ANY)

    int bind_result = bind(_serverSocket, (sockaddr*)&_serverAddress, sizeof(_serverAddress));
    if (bind_result < 0) {
        errorMessage("Failed to bind socket to port");
        return ;
    }

    int listenResult = listen(_serverSocket, _serverAddress.sin_port);
    if (listenResult < 0) {
        errorMessage("Failed to listen for incoming connections");
        return ;
    }

}

// void    Server::execute( void ) {

//     while (true) {
//         sockaddr_in clientAddress;
//         socklen_t clientAddressSize = sizeof(clientAddress);

//         // _Users.push_back() 

//     }
// }

Server::~Server( void ) { return ; }