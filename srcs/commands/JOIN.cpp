#include "commands.hpp"

void    joinChannel( std::string channelName, User &user )
{
    // if (user.getServer()->channelNameAlreadyUsed() == true)
        // join channel that already exists
    // else
        Channel  *newChannel = new Channel(channelName, *user.getServer(), user);

    // nick louise
    // user lola caro marie :louise a
    // JOIN #channel1

    //RPL :
    // :louise!lola@127.0.0.1 JOIN #channel1
    // :master.ircgod.com 353 louise = #channel1 :@louise (NAMES cmd)
    // :master.ircgod.com 366 louise #channel1 :End of NAMES list (NAMES cmd)
    // :master.ircgod.com 329 louise #channel1 1676390651 (RPL CREATION_TIME) -> wtf


}