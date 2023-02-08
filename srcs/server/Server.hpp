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
#include <map>
#include <vector>
#include "user/User.hpp"
#include "commands.hpp"

class User;

class Server 
{
    public :
        Server( void );
        ~Server( void );


        int                         getPort( void ) const;
        int                         getNbUsers( void ) const;
        int                         getMaxUsers( void ) const;
        std::string                 getVersion( void ) const;
        std::string                 getServerName( void ) const;
        std::string                 getPassword( void ) const;
        std::string                 getCreationDate( void ) const;
        std::vector<std::string>    getNickList(void)   const;
        std::map<std::string, void (*)(std::string params, User &user)>    getCommandMap(void)   const;

        void                        setPort( int port);
        void                        setPassword( std::string password );
        void                        setNbUsers( void );
        
        int                         runServer( void );
        int                         createSocket( void );
        sockaddr_in                 bindSocket( int serverSocket );
        void                        removeUser( int i );
        void                        addUser( int fd);

    private :
             
        int                         _port;
        std::string                 _version;
        std::string                 _serverName; //JLA
        std::string                 _password;
        std::string                 _creationDate;
        struct pollfd               _fds[200];

        std::map< int, User* >      _userMap;
        int                         _nbUsers;
        int                         _maxUsers;
        // std::vector< Channel >  _Channels;

        //Commands
        std::map<std::string, void (*)(std::string params, User &user)> _commandMap;

        //checknick
        std::vector<std::string>         _nickList;

};

#endif