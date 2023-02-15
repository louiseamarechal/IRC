# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "user/User.hpp"
#include "server/Server.hpp"
#include <vector>

class Server;
class User;

class Channel {

    public :
        Channel( std::string name, Server& server, User& channelCreator );
        ~Channel( void );

        std::string                     getChannelName( void ) const;
        std::vector<User&>              getChannelMembers( void ) const;

    private :
        // std::string                     _channelShortName;
        std::string                     _channelName;
        std::vector<User&>              _channelMembers; // est ce que Map est le plus approprie ? -> acceder a un User via son nickname
        Server&                         _server;
        User&                           _channelOperator;
        User&                           _channelCreator;

};

bool    channelNameFormatIsOk( std::string name );

#endif