#include "commands.hpp"

// :hey!gsd@127.0.0.1 JOIN #hey
void    sendJoinRpl( User &user, std::string channelName )
{
    std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    std::string rpl = ":" + user.getUserNick() + irssi + " JOIN " + channelName + "\r\n";
    // std::string rpl = ":" + user.getUserNick() + " JOIN " + channelName + "\r\n";

    if (user.getUserChannel().getChannelMembers().size() > 1)
        user.getUserChannel().sendMessageToEveryone(rpl, user.getUserFd());

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    std::cout << "[SEND] from Server to User FD#" << user.getUserFd() << " : " << rpl << std::endl;
    names(channelName, user);
}

void    joinChannel( std::string channelName, User &user )
{
    std::string errorMessage;
    std::cout << "JOIN COMMAND: " << std::endl;

    if (!user.getIsUserRegistered())
        return;

    // CHECKER SI USER IS NOT BANNED FROM CHANNEL

    // si le user fait deja parti d'un channel
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

    if ( user.getServer()->channels[channelName] == NULL )// si le channel n'existe pas encore
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
    else if ((user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) && user.getChannelName().empty()))
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


// 13:46 -!- louisea [] has joined #hey
// 13:46 [Users #hey]
// 13:46 [ louisea] 
// 13:46 -!- Irssi: #hey: Total of 1 nicks [1 ops, 0 halfops, 0 voices, 0 normal]


                                                                                                  
// 13:47 -!- louisea [~lmarecha@2169-197b-3cad-ad79-a88.210.62.ip] has joined #hey
// 13:47 [Users #hey]
// 13:47 [@louisea] 
// 13:47 -!- Irssi: #hey: Total of 1 nicks [1 ops, 0 halfops, 0 voices, 0 normal]
