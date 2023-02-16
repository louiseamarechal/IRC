#include "commands.hpp"

void    sendJoinRpl( User &user, std::string channelName )
{
    std::string symbol;
    std::string rpl = ":" + user.getUserNick() + " JOIN " + channelName + "\r\n";
    std::string rplThree;
    std::string rplOne;
    std::string nickNames;

    if (user.getUserChannel().getChannelOperator() == user.getUserNick())
        symbol = "@";
    else
        symbol = "";

    if (user.getUserChannel().getChannelMembers().size() > 1)
    {
        nickNames = user.getUserChannel().getAllMembersName();
        symbol = "@";
    }
    else
        nickNames = user.getUserNick();

    rplThree = sendMessage3(353, user, *user.getServer(), channelName, symbol, nickNames);
    rplOne = sendMessage1(366, user, *user.getServer(), channelName);

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    send(user.getUserFd(), rplThree.c_str(), rplThree.size(), 0);
    send(user.getUserFd(), rplOne.c_str(), rplOne.size(), 0);
}

void    joinChannel( std::string channelName, User &user )
{
    std::string errorMessage;
    // si le user fait deja parti d'un channel

    if (!user.getIsUserRegistered())
        return;

    if (!(user.getChannelName().empty()))
    {
        errorMessage = sendMessage1(405, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (channelName.empty())
    {
        errorMessage = sendMessage1(461, user, *user.getServer(), "JOIN");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if ( user.getServer()->channels.empty() )// si le channel n'existe pas encore
    {
        if (!channelNameFormatIsOk(channelName))
        {
            errorMessage = sendMessage1(476, user, *user.getServer(), channelName);
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
            return;
        }

        Channel  *newChannel = new Channel(channelName, *user.getServer(), user);

        // ajouter le channel a userChannel (il est ajoute a _channelMembers dans le constructeur + designe as channelOperator & channelCreator)
        user.setUserChannel(newChannel);

        //ajouter le Channel a la plublic map du server channels
        user.getServer()->setChannels(newChannel);
        sendJoinRpl(user, channelName);
        return;
    }
    
    // si le Channel existe et que User n'est pas deja dans un autre channel
    if ((user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) && user.getChannelName().empty()))
    {
    // add channel object to user
        user.setUserChannel(user.getServer()->channels[channelName]);
    
    // si user not already in _channelMembers list on l'y ajoute
        user.getServer()->channels[channelName]->addChannelMembers(user);
        sendJoinRpl(user, channelName);
    }
}

// 461 ERR_NEEDMOREPARAMS ---- done
// 476 ERR_BADCHANMASK ------- done
// 405 ERR_TOOMANYCHANNELS --- done
// 471 ERR_CHANNELISFULL ----- we don't limit the access
// 403 ERR_NOSUCHCHANNEL ----- if a channel doesn't exists we create it
// 407 ERR_TOOMANYTARGETS ---- we don't do safe channels
// 332 RPL_TOPIC ------------- we don't do TOPIC
// 474 ERR_BANNEDFROMCHAN ---- we don't allow operators to ban people
// 437 ERR_UNAVAILRESOURCE --- we don't do it