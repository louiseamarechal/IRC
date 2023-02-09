#include "channel/Channel.hpp"

Channel::Channel( std::string name, Server* server, User* channelCreator ) : _channelName(name), _channelServer(server), _channelOperator(channelCreator), _channelCreator(channelCreator)
{
    return ;
}

Channel::~Channel( void ) { return; }