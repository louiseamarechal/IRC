#include "commands.hpp"
#include "reply.hpp"


void    quit(std::string params, User &user)
{
    (void) params;
    if (user.getIsUserRegistered() == false)
    {
       close(user.getUserFd());
       return;
    }
    if (!user.getChannelName().empty())
        partChannel(user.getChannelName(), user);
    if (user.getUserNick().empty() == false)
        user.getServer()->removeNickList(user.getUserNick());
    close(user.getUserFd()); 
    user.getServer()->removeUserWithFd(user.getUserFd());
     
}