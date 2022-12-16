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

    public :
        User( void );
        ~User( void );

        int         getUserSocket() const;
        std::string getUserNick() const;
        std::string getUserLoggin() const;
        std::string getUserFullName() const;

        void        setUserSocket();
        void        setUserNick();
        void        setUserLoggin();
        void        setUserFullName();

    private :
        std::string userLoggin; // jbouyer
        std::string userFullName; // Jacinthe Bouyer
        std::string userNick; // coucou
        int         clientSocket; // user fd -> return de accept()
        
};

#endif