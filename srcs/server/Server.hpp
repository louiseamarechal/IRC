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
#include "channel/Channel.hpp"

class User;
class Channel;

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
        void                        setNickList(std::string nick);
        void                        setChannels( Channel* channel );
        
        void                        removeNickList(std::string oldNick);
        int                         runServer( void );
        int                         createSocket( void );
        sockaddr_in                 bindSocket( int serverSocket );
        void                        removeUser( int i );
        void                        addUser( int fd);
        int                         acceptconnexion(int server_fd);
        bool                        channelNameAlreadyUsed( std::string channelName );
        bool                        channelIsOkToJoin( Channel& channel );

    private :
             
        int             _port;
        std::string     _version;
        std::string     _serverName; //JLA
        std::string     _password;
        std::string     _creationDate;
        struct pollfd   _fds[200];

        // USER
        std::map< int, User* >              _userMap;
        int                                 _nbUsers;
        int                                 _maxUsers;

        //CHANNEL
        std::map< std::string, Channel* >   _channels; // should be a map
        std::vector< std::string >          _channelNames;

        //Commands
        std::map<std::string, void (*)(std::string params, User &user)> _commandMap;

        //checknick
        std::vector<std::string>         _nickList;

};

#endif