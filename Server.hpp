# ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <iostream>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <vector>
#include "User.hpp"

class User;

class Server {

    public :
        Server( void );
        ~Server( void );

        void    execute( void );

    // private :
        sockaddr_in         _serverAddress; // (AF_INET, PORT, etc)
        int                 _serverSocket; // retour de socket()
        unsigned int        _nbFds;             
        struct pollfd       _fds[200];
        std::string         _serverName; //JLA

        std::vector< User > _Users;        
};

#endif