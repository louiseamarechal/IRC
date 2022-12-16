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
#include <User.hpp>


class Server {

    Class User;

    public :
        Server( void );
        ~Server( void );

    private :
        sockaddr_in     server_address;
        int             server_socket;
        struct pollfd   fds[200];

        
}