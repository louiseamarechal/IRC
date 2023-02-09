# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "user/User.hpp"
#include "server/Server.hpp"

class Server;
class User;

class Channel {

    public :
        Channel( std::string name, Server* server, User* channelCreator );
        ~Channel( void );

    private :
        // std::string                     _channelShortName;
        std::string                     _channelName;
        std::map<std::string, User *>   _channelMembers; // est ce que Map est le plus approprie ? -> acceder a un User via son nickname
        Server*                         _channelServer;
        User*                           _channelOperator;
        User*                           _channelCreator;

};

#endif