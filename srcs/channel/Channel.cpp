#include "channel/Channel.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Channel::Channel( std::string name, Server& server, User& channelCreator ) : _server(server), _channelOperator(channelCreator), _channelCreator(channelCreator)
{
    if ( channelNameIsOk(name) )
        _channelName = name;
    
    _channelMembers.push_back(_channelOperator);
    server.setChannels(this);

    return ;
}

Channel::~Channel( void ) { return; }

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

std::string Channel::getChannelName( void ) const { return (_channelName); }

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

bool    channelNameIsOk( std::string name )
{
    if ( name.length() > 200 || name.length() < 1 )
        return (false);
    if ( (name.find(',') != std::string::npos) || (name.find(7) != std::string::npos) )
        return (false);
    if (name[0] != '#' || name[0] != '&') // '#' = channel available across IRC network -> '&' available on local server only
        return (false);
    
    return (true);
}