#include "channel/Channel.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Channel::Channel( std::string name, Server& server, User& user ) : _channelMembers(std::vector<User*>()),
                                                                _server(server),
                                                                _channelOperator(user.getUserNick()), 
                                                                _channelCreator(user.getUserNick())
{
    // on set les attributs
        // si format de name ok seuelement on set le name
            // sinon TBC
    
    // on ajoute le channel operator a la liste des membres
    // on set up le channel dans server (on l'ajoute a la liste des channels + on ajoute le nom a la channelName liste)
    if ( channelNameFormatIsOk(name))
        _channelName = name;
    else
    {
        std::string errorMessage = sendMessage1(476, user, server, name);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    std::cout << "Channel created ! " << _channelName << std::endl;

    addChannelMembers(user);
    server.setChannels(this);

    return ;
}

Channel&    Channel::operator=( Channel const & rhs )
{
    if (this != &rhs)
    {
        _channelName = rhs.getChannelName();
        _channelMembers = rhs.getChannelMembers();
        _server = getChannelServer();
        _channelOperator = getChannelOperator();
        _channelCreator = getChannelCreator();
    }

    return (*this);
}

Channel::~Channel( void ) { return; }

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

std::string         Channel::getChannelName( void ) const { return (_channelName); }
std::vector<User*>  Channel::getChannelMembers( void ) const { return (_channelMembers); }
std::string         Channel::getChannelCreator( void ) const { return (_channelCreator); }
std::string         Channel::getChannelOperator( void ) const { return (_channelOperator); }
Server&             Channel::getChannelServer( void ) const { return (_server); }

std::string         Channel::getAllMembersName( void ) const
{
    std::vector<User*>::const_iterator    it;
    std::string                     membersNames;

    for (it = _channelMembers.begin(); it != _channelMembers.end(); it++)
        membersNames += (*it)->getUserNick() + " ";
    
    return (membersNames);
}


/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

void    Channel::addChannelMembers( User& user )
{
    std::vector<User*>::iterator    it;
    std::string                     userNick = user.getUserNick();

    for (it = _channelMembers.begin(); it != _channelMembers.end(); it++)
    {
        if ((*it)->getUserNick() == userNick)
        {
            std::cout << "User is already in the _channelMembers vector" << std::endl;
            return;
        }
    }

    _channelMembers.push_back(&user);
    std::cout << user.getUserNick() << " is now part of the _channelMembers List" << std::endl;
    
    return;
}

bool    channelNameFormatIsOk( std::string name )
{
    std::cout << "name[0]" << name[0] << std::endl;
    if ( name.length() > 200 || name.length() < 1 )
    {
        std::cout << "It's a length issue ! Whuuut " << std::endl;
        return (false);
    }
    if ( (name.find(',') != std::string::npos) || (name.find(7) != std::string::npos) )
    {
        std::cout << "I found a , or a 7char ! Whuuut " << std::endl;
        return (false);
    }
    if (name[0] != '#' && name[0] != '&') // '#' = channel available across IRC network -> '&' available on local server only
    {
        std::cout << "First char is not ok ! Whut whut ! Show me what u got : " << name[0] << std::endl;
        return (false);
    }
    
    return (true);
}