#include "commands.hpp"
#include "channel/Channel.hpp"

void    sendJoinRpl( User &user, std::string channelName )
{
    std::string symbol;
    std::string rpl = ":" + user.getUserNick() + " JOIN " + channelName + "\r\n";
    std::string rplThree;
    std::string rplOne;
    std::string nickNames;

    if (user.getUserChannel().getChannelMembers().size() > 1)
        nickNames = user.getUserChannel().getAllMembersName();
    else
        nickNames = user.getUserNick();

    if (user.getUserChannel().getChannelOperator() == user.getUserNick())
        symbol = "@";
    else
        symbol = "";

    rplThree = sendMessage3(353, user, *user.getServer(), channelName, symbol, nickNames);
    rplOne = sendMessage1(366, user, *user.getServer(), channelName);

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    send(user.getUserFd(), rplThree.c_str(), rplThree.size(), 0);
    send(user.getUserFd(), rplOne.c_str(), rplOne.size(), 0);
}

void    joinChannel( std::string channelName, User &user )
{
    // si le user fait deja parti d'un channel
    if (!(user.getChannelName().empty()))
        return;

    if ( user.getServer()->channels.empty() )// si le channel n'existe pas encore
    {
        if (!channelNameFormatIsOk(channelName))
        {
            std::string errorMessage = sendMessage1(476, user, *user.getServer(), channelName);
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
            return;
        }

        Channel  *newChannel = new Channel(channelName, *user.getServer(), user);

        // ajouter le channel a userChannel (il est ajoute a _channelMembers dans le constructeur + designe as channelOperator & channelCreator)
        user.setUserChannel(newChannel);

        //ajouter le Channel a la map du server _channels
        user.getServer()->setChannels(newChannel);
        sendJoinRpl(user, channelName);
        return;
    }
    
    std::string serverChannelName = user.getServer()->channels[channelName]->getChannelName();
    std::cout << "Channel name = " << serverChannelName << std::endl;
    std::cout << "Can I join the channel ? " << user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) << std::endl;
    std::cout << "I am not appart of a channel ! " << user.getChannelName().empty() << std::endl;

    if ((user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) && user.getChannelName().empty()))
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