#include "commands.hpp"

bool    isEverythingOkNotice( std::string params, User& user)
{
    std::vector<std::string> splittedBufer;
    std::string msgTarget;

    if (params.empty())
        return (false);

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));

    if (splittedBufer.size() != 2 )
        return (false);

    msgTarget = splittedBufer[0];

    if (!isInVectorList(msgTarget, user.getServer()->getNickList()) && !isInVectorList(msgTarget, user.getServer()->getChannelNames())) // si user/channel n'existe pas
        return (false);

    if (splittedBufer[1].empty())
        return (false);

    return (true);
}

void    notice( std::string params, User& user )
{
    std::string msgTarget;
    std::string rpl;
    std::string irssi;
    std::vector<std::string> splittedBufer;

    if (!isEverythingOkNotice(params, user))
        return;

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));
    msgTarget = splittedBufer[0];
    irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    rpl = ":" + user.getUserNick() + irssi + " NOTICE " + msgTarget + " :" + splittedBufer[1] + "\r\n"; 
    
    std::cout << "[PRIVMSG] - msgTarget = " << msgTarget << std::endl;
    std::cout << "[PRIVMSG] - message = " << splittedBufer[1] << std::endl;
    std::cout << "[PRIVMSG] - rpl = " << rpl << std::endl;

    if (msgTarget[0] == '#' || msgTarget[0] == '&') // target = channel
    {
        if (user.getChannelName() != msgTarget)  // si user est pas dans ce channel
            return;
        user.getServer()->sendMessageToAllChannelMembers(rpl, user.getUserFd());
    }
    else
    {
        const User&   userTarget = user.getServer()->getUser(msgTarget);

        user.getServer()->sendPrivMessages(rpl, user.getUserFd(), userTarget.getUserFd());
    }
}