#include "commands.hpp"

void    motd(std::string params, User &user) {

    std::string         motdStart;
    std::string         motd;
    std::string         motdEnd;
    std::string         errorMessage;
    std::ifstream       file("MOTD.txt");
    std::stringstream   buffer;

    if (user.getIsUserRegistered() == false)
    {
        errorMessage = sendMessage(451, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if ( params.empty() || params == "JLA.irc.com" )
    {
        buffer << file.rdbuf();

        motdStart = sendMessage1(375, user, *(user.getServer()), user.getServer()->getServerName());
        motd = sendMessage1(372, user, *(user.getServer()), buffer.str());
        motdEnd = sendMessage(376, user, *(user.getServer()));
        
        send(user.getUserFd(), motdStart.c_str(), motdStart.size(), 0);
        send(user.getUserFd(), motd.c_str(), motd.size(), 0);
        send(user.getUserFd(), motdEnd.c_str(), motdEnd.size(), 0);
        return;
    }

    errorMessage = sendMessage(422, user, *(user.getServer()));
    send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
}