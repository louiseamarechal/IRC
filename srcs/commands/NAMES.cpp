#include "commands.hpp"

void    names( std::string channelName, User &user )
{
    std::string rplThree;
    std::string rplOne;
    std::string nickNames;

    if (user.getChannelName().empty())
        return;

    nickNames = user.getUserChannel().getAllMembersName();
    
    rplThree = sendMessage2(353, user, *user.getServer(), channelName, user.getUserChannel().getAllMembersName());
    rplOne = sendMessage1(366, user, *user.getServer(), channelName);

    send(user.getUserFd(), rplThree.c_str(), rplThree.size(), 0);
    send(user.getUserFd(), rplOne.c_str(), rplOne.size(), 0);

    std::cout << "[SEND] from Server to User FD#" << user.getUserFd() << " : " << rplThree << std::endl;
    std::cout << "[SEND] from Server to User FD#" << user.getUserFd() << " : " << rplOne << std::endl;
    std::cout << channelName << " members are : " << nickNames << std::endl;
}