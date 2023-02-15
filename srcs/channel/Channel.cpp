#include "channel/Channel.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Channel::Channel( std::string name, Server& server, User& channelCreator ) : _server(server), _channelOperator(channelCreator), _channelCreator(channelCreator)
{
    // on set les attributs
        // si format de name ok seuelement on set le name
            // sinon TBC
    
    // on ajoute le channel operator a la liste des membres
    // on set up le channel dans server (on l'ajoute a la liste des channels + on ajoute le nom a la channelName liste)

    if ( channelNameFormatIsOk(name) && !(server.channelNameAlreadyUsed(name)))
        _channelName = name;
    
    _channelMembers.push_back(_channelOperator);
    server.setChannels(this);

    return ;
}



Channel::~Channel( void ) { return; }

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

std::string         Channel::getChannelName( void ) const { return (_channelName); }
std::vector<User&>  Channel::getChannelMembers( void ) const { return (_channelMembers); }

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

bool    channelNameFormatIsOk( std::string name )
{
    if ( name.length() > 200 || name.length() < 1 )
        return (false);
    if ( (name.find(',') != std::string::npos) || (name.find(7) != std::string::npos) )
        return (false);
    if (name[0] != '#' || name[0] != '&') // '#' = channel available across IRC network -> '&' available on local server only
        return (false);
    
    return (true);
}

// On remove un Channel si :
    // le dernier user a quitte le Channel.
        // quand un user quitte le Channel (PART) on clear user._channelName()
        // on le remove de _channelMembers
            // si c'est le dernier dans _channelMembers on delete le channel de server._channels

// Quand on remove un Channel on doit :
    // le laisser dans _channelNames -> une fois qu'un nom de channel a existe il a plus de droit d'etre repris
    // supprimer le channel du vector dans server._channels
    // supprimer l'objet channel cree dans joinChannel