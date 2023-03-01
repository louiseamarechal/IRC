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
#include <exception>
#include "user/User.hpp"
#include "commands.hpp"
#include "channel/Channel.hpp"
#include "utils.hpp"

class User;
class Channel;
class exception;

class Server 
{
    public :
        Server( void );
        ~Server( void );


        int                                                             getPort( void ) const;
        int                                                             getNbUsers( void ) const;
        int                                                             getMaxUsers( void ) const;
        std::string                                                     getVersion( void ) const;
        std::string                                                     getServerName( void ) const;
        std::string                                                     getPassword( void ) const;
        std::string                                                     getCreationDate( void ) const;
        std::vector<std::string>                                        getNickList(void)   const;
        std::vector<std::string>                                        getChannelNames(void)   const;
        // std::map< std::string, Channel* >                               getChannels( void ) const;
        // Channel*                                                        getChannel( std::string channelName ) const;
        const std::map< int, User* >&                                   getUserMap( void ) const;
        const User&                                                     getUser( std::string nickName ) const;
        const std::map<std::string, void (*)(std::string params, User &user)>& getCommandMap(void)   const;

        void                                                            setPort( int port);
        void                                                            setPassword( std::string password );
        void                                                            setNbUsers( void );
        void                                                            setNickList(std::string nick);
        void                                                            setChannels( Channel* channel );
        
        int                                                             runServer( void );
        int                                                             createSocket( void );
        sockaddr_in                                                     bindSocket( int serverSocket );
        void                                                            removeUser( int i );
        void                                                            removeUserWithFd( int fd );
        void                                                            addUser( int fd);
        int                                                             acceptconnexion(int server_fd);
        static void                                                     sigintHandler(int sig);

        void                                                            cDuPropre( void );
        // void                         disconnect_all(void);
        
        void                                                            removeNickList(std::string oldNick);
        bool                                                            channelIsOkToJoin( Channel& channel );
        void                                                            sendMessageToAllChannelMembers( std::string buffer, int fd );
        void                                                            deleteChannel( Channel* channel );
        void                                                            sendPrivMessages( std::string buffer, int userFd, int targetFd );
        std::map< std::string, Channel* >                               channels;
        
    private :
             
        int                         _port;
        std::string                 _version;
        std::string                 _serverName; //JLA
        std::string                 _password;
        std::string                 _creationDate;
        struct pollfd               _fds[200];
        int                         _nbUsers;
        std::map< int, User* >      _userMap;
        
        int                         _maxUsers;
        int                          _serverFd;
        int                          _epollFd;

        
        std::vector< std::string >           _channelNames;

        //Commands
        std::map<std::string, void (*)(std::string params, User &user)> _commandMap;

        //checknick
        std::vector<std::string>         _nickList;


};

// extern Server*                  global_serv;
// extern std::vector<int>         g_fdList;
extern bool interrupt;

#endif