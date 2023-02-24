#include "commands.hpp"

std::vector<std::string> splitPrivmsgBuffer( std::string params )
 {

    std::vector<std::string>        splittedParams;
    char                            whitespace = 32;
    std::string::iterator           it = params.begin();
    std::string                     result;

    if (params.empty())
        return (splittedParams);

    for (it = params.begin(); it != params.end(); ++it)
    {
        result += *it; // copie each charactere to result
        if (*it == whitespace || (it + 1) == params.end())
        {
                if (*it == whitespace)
                    result.erase(result.size() - 1); // remove whitespace at the end of result
                splittedParams.push_back(result); // add result to the vector
                break;
        };
    }
    params.erase(0, result.size());
    while (params[0] == whitespace || params[0] == ':')
        params.erase(0, 1);
    splittedParams.push_back(params);
    return (splittedParams);
}

void    sendErrorPvmsg(int code, User& user, std::string param)
{
    std::string errorMessage;

    if (code == 412)
        errorMessage = sendMessage(code, user, *user.getServer());
    else
        errorMessage = sendMessage1(code, user, *user.getServer(), param);
    
    send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
}

bool    isEverythingOkPrivMsg( std::string params, User& user)
{
    std::vector<std::string> splittedBufer;
    std::string msgTarget;

    if (params.empty())
    {
        sendErrorPvmsg(412, user, ""); // ERR_NOTEXTTOSEND
        sendErrorPvmsg(411, user, "PRIVMSG"); // ERR_NORECIPIENT
        return (false);
    }

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));

    if (splittedBufer.size() != 2 )
    {
        if (splittedBufer.size() < 2)
            sendErrorPvmsg(412, user, ""); // ERR_NOTEXTTOSEND
        else if (splittedBufer.size() > 2)
            sendErrorPvmsg(407, user, splittedBufer[0]); // ERR_TOOMANYTARGETS

        return (false);
    }

    msgTarget = splittedBufer[0];

    if (!isInVectorList(msgTarget, user.getServer()->getNickList()) && !isInVectorList(msgTarget, user.getServer()->getChannelNames())) // si user/channel n'existe pas
    {
        sendErrorPvmsg(401, user, splittedBufer[0]);// ERR_NOSUCHNICK
        return (false);
    }

    if (splittedBufer[1].empty())
    {
        sendErrorPvmsg(412, user, ""); // ERR_NOTEXTTOSEND
        return (false);
    }

    return (true);
}

void    sendPrivMsg( std::string params, User& user )
{
    std::string msgTarget;
    std::string rpl;
    std::string irssi;
    std::vector<std::string> splittedBufer;

    if (!isEverythingOkPrivMsg(params, user))
        return;

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));
    msgTarget = splittedBufer[0];
    irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    rpl = ":" + user.getUserNick() + irssi + " PRIVMSG " + msgTarget + " :" + splittedBufer[1] + "\r\n"; 
    
    std::cout << "[PRIVMSG] - msgTarget = " << msgTarget << std::endl;
    std::cout << "[PRIVMSG] - message = " << splittedBufer[1] << std::endl;
    std::cout << "[PRIVMSG] - rpl = " << rpl << std::endl;

    if (msgTarget[0] == '#' || msgTarget[0] == '&') // target = channel
    {
        if (user.getChannelName() != msgTarget)  // si user est pas dans ce channel
        {
            sendErrorPvmsg(404, user, msgTarget); // ERR_CANNOTSENDTOCHAN
            return;
        }
        user.getServer()->sendMessageToAllChannelMembers(rpl, user.getUserFd());
    }
    else
    {
        const User&   userTarget = user.getServer()->getUser(msgTarget);

        user.getServer()->sendPrivMessages(rpl, user.getUserFd(), userTarget.getUserFd());
    }
}

// ERR_NORECIPIENT
// ERR_CANNOTSENDTOCHAN
// ERR_NOSUCHNICK
// ERR_NOTEXTTOSEND
// ERR_TOOMANYTARGETS
// RPL_AWAY ----------- a voir si on fait
// ERR_NOTOPLEVEL ----- a voir si on fait
// ERR_WILDTOPLEVEL --- a voir si on fait