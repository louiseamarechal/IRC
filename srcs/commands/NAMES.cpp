#include "commands.hpp"

void    names( std::string channelName, User &user )
{
    std::string rplThree;
    std::string rplOne;
    std::string nickNames;

    if (!user.getIsUserRegistered())
    {
      std::string errorMessage = sendMessage(451, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    } 

    if (user.getChannelName().empty())
        return;

    nickNames = user.getUserChannel().getAllMembersName();
    
    rplThree = sendMessage2(353, user, *user.getServer(), channelName, user.getUserChannel().getAllMembersName());
    rplOne = sendMessage1(366, user, *user.getServer(), channelName);

    send(user.getUserFd(), rplThree.c_str(), rplThree.size(), 0);
    send(user.getUserFd(), rplOne.c_str(), rplOne.size(), 0);
}