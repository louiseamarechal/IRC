#include "commands.hpp"

// only used if User is in a channel

    // USER
    // delete/remove _userChannel
    // clear _channelName

    // CHANEL
    // remove User de _channelMembers
        // clear _channelOperator ->  remplace par qui ?
         // clear _channelCreator -> remplace par qui ?

// if  User is the last Member of the Channel

    // SERVER :
    // delete server.channels
    // remove de _channelNames

void    partChannel(std::string params, User &user)
{
    std::string                 channelName;
    std::string                 partMessage;
    std::vector<std::string>    splittedParams;
    std::string                 errorMessage;
    std::string rpl;

    if (params.empty())
    {
        errorMessage = sendMessage1(461, user, *user.getServer(), "PART");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    splittedParams = splitString(params);
    channelName = splittedParams[0];
    std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    rpl = ":" + user.getUserNick() + irssi + " PART " + channelName + "\r\n";

    std::cout << "[PART] - Splitted Params size : " << (int)splittedParams.size() << std::endl;
    if (splittedParams.size() > 1)
        partMessage = splittedParams[1];

    std::cout << "[PART] - Channel Name : " << channelName << std::endl;
    if (user.getServer()->channels[channelName] == NULL) // channel n'existe pas
    {
        errorMessage = sendMessage1(403, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (user.getChannelName() != channelName) // user not in this channel
    {
        errorMessage = sendMessage1(442, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

     if (user.getUserChannel().getChannelMembers().size() > 1)
        user.getUserChannel().sendMessageToEveryone(rpl, user.getUserFd());
    
    // std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    std::cout << "[PART][SEND] from Server to User FD#" << user.getUserFd() << " : " << rpl << std::endl;
    user.clearChannel(); // clear channelName + _userChannel pointe sur NULL
    user.getServer()->channels[channelName]->removeChannelMembers(user); // remove User de _channelMembers + delete le channel dans server
}

// 461 ERR_NEEDMOREPARAMS --- done
// 442 ERR_NOTONCHANNEL ----- done
// 403 ERR_NOSUCHCHANNEL ---- done

// sendMessageToEveryone

// :louise!gdfs@127.0.0.1 JOIN #hey
// :louise!gdfs@127.0.0.1 PART #hey :

// join #hey
// :hey!gsd@127.0.0.1 JOIN #hey
// :master.ircgod.com 353 hey = #hey :@louisea  hey 
// :master.ircgod.com 366 hey #hey :End of NAMES list
// :master.ircgod.com 329 hey #hey 1676632377
// hello (from irssi)
// :master.ircgod.com 421 hey HELLO :Unknown command
// :louisea!lmarecha@127.0.0.1 PRIVMSG #hey :hello
// PING :master.ircgod.com
