#include "commands.hpp"

void    joinChannel( std::string channelName, User &user )
{
    if (user.getServer()->channelIsOkToJoin(user.getChannel()) && user.getChannelName().empty()) // si le channel est ouvert et que le user ne fait pas parti d'un autre channel
        // join channel that already exists
        // ajouter le channelName a user._channelName
        // si user not already in _channelMembers list
            // ajouter le user a channel._channelMembers
    
    // else si le channelName est ok (not used before)
        // creer le nouveau channel
        // Channel  *newChannel = new Channel(channelName, *user.getServer(), user);
        // ajouter le channelName a user._channelName
            // user ajoute a _channelMembers dans le constructeur + designe as channelOperator & channelCreator

    // let the user receive all channel messages + receive PRIVMSG from other channelMembers
    // envoyer les RPL



// HOW IT SHOOULD BEHAVE
    // nick louise
    // user lola caro marie :louise a
    // JOIN #channel1

    //RPL :
    // :louise!lola@127.0.0.1 JOIN #channel1
    // :master.ircgod.com 353 louise = #channel1 :@louise (NAMES cmd)
    // :master.ircgod.com 366 louise #channel1 :End of NAMES list (NAMES cmd)
    // :master.ircgod.com 329 louise #channel1 1676390651 (RPL CREATION_TIME) -> wtf


}