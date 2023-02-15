#include "commands.hpp"
#include "channel/Channel.hpp"

void    sendJoinRpl( User &user, std::string channelName )
{
    std::string symbol;
    std::string rpl = ":" + user.getUserNick() + " JOIN " + channelName + "\r\n";;
    std::string rpl353 = sendMessage3(353, user, *user.getServer(), channelName, symbol, user.getUserNick());;
    std::string rpl366 = sendMessage1(366, user, *user.getServer(), channelName);;

    if (user.getUserChannel().getChannelOperator() == user.getUserNick())
        symbol = "@";
    else
        symbol = "";

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    send(user.getUserFd(), rpl353.c_str(), rpl353.size(), 0);
    send(user.getUserFd(), rpl366.c_str(), rpl366.size(), 0);
}

void    joinChannel( std::string channelName, User &user )
{
    // Server* server = user.getServer(); // Récupération de la référence de Server à partir de User
    // Channel& channel = server->getChannel(channelName); // Récupération de la référence de Channel correspondant au nom channelName
    // channel.addChannelMembers(user); // Ajout de la référence de User à la variable _channelMembers de Channel


    // si le channel est ouvert et que le user ne fait pas parti d'un autre channel
    if ( user.getServer()->channels.empty() )// si le channel n'existe pas encore
    {
        // creer le nouveau channel
        Channel  *newChannel = new Channel(channelName, *user.getServer(), user);

        // if (newChannel == NULL)
        //     return;
        
        // ajouter le channel a userChannel
            // user ajoute a _channelMembers dans le constructeur + designe as channelOperator & channelCreator
        user.setUserChannel(newChannel);

        //ajouter le Channel a la map du server _channels
        user.getServer()->setChannels(newChannel);
        sendJoinRpl(user, channelName);
        return;
    }
    
    std::string userChannelName = user.getUserChannel().getChannelName();
    std::cout << "Channel name = " << userChannelName << std::endl;

    if ((user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) && userChannelName.empty()))
    {
    // add channel to user
    user.setUserChannel(user.getServer()->channels[channelName]);
    
    // si user not already in _channelMembers list
        // user ajoutee a channel._channelMembers dans setUserChannel;
    user.getServer()->channels[channelName]->addChannelMembers(user);
    // user.addUserToChannel( channelName );
    sendJoinRpl(user, channelName);
    }

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