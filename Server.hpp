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


        int                 getPort( void ) const;
        int                 getNbUsers( void ) const;
        std::string         getServerName( void ) const;
        std::string         getPassword( void ) const;

        void                setPort(int port);
        void                setServerName(std::string serverName);
        void                setPassword(std::string password);
        void                setNbUsers(int nbUsers);
        
        void                runServer( void );
        int                 createSocket( void );
        sockaddr_in         bindSocket( int serverSocket );

    private :
             
        int                 _port;
        std::string         _serverName; //JLA
        std::string         _password;
        struct pollfd       _fds[200];

        std::vector< User >     _Users;
        int                     _nbUsers;
        // std::vector< Channel >  _Channels;

};

#endif