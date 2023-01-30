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
#include <vector>
#include <map>
#include "Server.hpp"
#include "commands.hpp"

class Server;

class Command;
class User {

   

    public :
        User( int fd, Server &server );
        // User( int fd, Server* server); // strUser a parser avec toutes les param prives
        ~User( void );

        int                                     getUserFd() const;
        std::string                             getUserNick() const;
        std::string                             getUserLoggin() const;
        std::string                             getUserFullName() const;
        bool                                    getIsUserRegistered() const;
        bool                                    getIsNickSet() const;
        bool                                    getIsUserSet() const;
        Server&                                 getServer() const;

        // void        setUserFd( int fd );
        void                                    setUserNick( std::string nick );
        void                                    setUserLoggin( std::string loggin );
        void                                    setUserFullName( std::string fullName );
        // std::map< std::string, std::string >    commandParser( std::string buffer );
        void                                    setIsNickSet(bool value);
        void                                    setIsUserRegistered(bool value);

        void                                     handleCommand(std::string buffer);

    private :
        std::string                             _userLoggin; // jbouyer
        std::string                             _userFullName; // Jacinthe Bouyer
        std::string                             _userNick; // coucou
        int                                     _userFd; // user fd -> return de accept()
        bool                                    _isNickSet;
        bool                                    _isUserSet;
        bool                                    _isUserRegistered;
        Server&                                  _server;
};

#endif