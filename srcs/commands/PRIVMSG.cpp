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

void    sendPrivMsg( std::string params, User& user )
{
    std::string errorMessage;
    std::string msgTarget;
    std::string rpl;
    std::vector<std::string> splittedBufer;

    if (params.empty())
    {
        errorMessage = sendMessage1(411, user, *user.getServer(), "PRIVMSG");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0); // ERR_NORECIPIENT
        send(user.getUserFd(), sendMessage(412, user, *user.getServer()).c_str(), sendMessage(412, user, *user.getServer()).size(), 0); // ERR_NOTEXTTOSEND
        return;
    }

    params = removeConsecutiveWhitespace(params);
    splittedBufer = splitPrivmsgBuffer(params);

    msgTarget = splittedBufer[0];
    std::cout << "PRIVMSG - msgTarget = " << msgTarget << std::endl;

    if (splittedBufer.size() != 2 )
    {
        if (splittedBufer.size() < 2)
        {
            errorMessage = sendMessage(412, user, *user.getServer());
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0); // ERR_NOTEXTTOSEND
        }
        else if (splittedBufer.size() > 2)
        {
            errorMessage = sendMessage1(407, user, *user.getServer(), splittedBufer[0]);
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0); // ERR_NOTEXTTOSEND
        }
        return;
    }

    // PRIVMSG #hey :hey
    std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    rpl = ":" + user.getUserNick() + irssi + " PRIVMSG " + msgTarget + " :" + splittedBufer[1] + "\r\n"; 
    std::cout << "PRIVMSG - message = " << splittedBufer[1] << std::endl;
    std::cout << "PRIVMSG - rpl = " << rpl << std::endl;

    // si user/channel n'existe pas -> ERR_NOSUCHNICK
    if (!isInVectorList(msgTarget, user.getServer()->getNickList()) && !isInVectorList(msgTarget, user.getServer()->getChannelNames()))
    {
        errorMessage = sendMessage1(401, user, *user.getServer(), msgTarget);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0); // ERR_NOSUCHNICK
        return;
    }

    if (msgTarget[0] == '#' || msgTarget[0] == '&') // target = channel
    {
        std::cout << "Target is a Channel, here's the proof : " << msgTarget[0] << std::endl;
        user.getServer()->sendMessageToAllChannelMembers(rpl, user.getUserFd());
        return;
    }
    else
    {
        const User&   userTarget = user.getServer()->getUser(msgTarget);

        std::cout << "I Found the userTarget look at his fd: " << userTarget.getUserFd() <<std::endl;
        // if (user.getChannelName() != )
        // sinon target = user
        // check if user exists -> ERR_NOSUCHNICK
        // check if both user are in same channel -> ERR_CANNOTSENDTOCHAN
        // find userFD
        // send message to that user only
        // return;
    }

    //Check si buffer.empty()
        // si oui : ERR_NORECIPIENT
        // si non : split en deux variables -> msgTarget & message 
            // check que msgTarget exists (user ou channel)
                // si non : ERR_NOSUCHNICK (same pour les deux)
                // si plus de 1 target : 
                    // ERR_TOOMANYTARGETS
            // si message.empty()
                // ERR_NOTEXTTOSEND

    // Used to send message to all users of a Channel
        // check if the user is in this channel
            // si non : ERR_CANNOTSENDTOCHAN
        // send message to all personnes in the channel

    // Used to send prvmsg to users
        // check if both users are in the same channel
        // send message only to that user

}

// ERR_NORECIPIENT
// ERR_CANNOTSENDTOCHAN
// ERR_NOSUCHNICK
// ERR_NOTEXTTOSEND
// ERR_TOOMANYTARGETS
// RPL_AWAY ----------- a voir si on fait
// ERR_NOTOPLEVEL ----- a voir si on fait
// ERR_WILDTOPLEVEL --- a voir si on fait