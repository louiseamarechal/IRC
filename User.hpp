# ifndef USER_HPP
# define USER_HPP

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

class User {

    class Server;

    public :
        User( void );
        User( int fd ); // strUser a parser avec toutes les param prives
        ~User( void );

        int         getUserFd() const;
        std::string getUserNick() const;
        std::string getUserLoggin() const;
        std::string getUserFullName() const;

        // void        setUserFd( int fd );
        void        setUserNick( std::string nick );
        void        setUserLoggin( std::string loggin );
        void        setUserFullName( std::string fullName );

        // Command     handleBuffer( std::string buffer );

    private :
        std::string _userLoggin; // jbouyer
        std::string _userFullName; // Jacinthe Bouyer
        std::string _userNick; // coucou
        int         _userFd; // user fd -> return de accept()
        
};

#endif