#include "commands.hpp"
#include "reply.hpp"


void    quit(std::string params, User &user)
{
    (void) params;
    if (user.getIsUserRegistered() == true)
        user.getServer()->removeNickList(user.getUserNick());
    close(user.getUserFd());
}