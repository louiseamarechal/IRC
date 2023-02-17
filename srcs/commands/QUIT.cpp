#include "commands.hpp"
#include "reply.hpp"


void    quit(std::string params, User &user)
{
    (void) params;
    if (user.getUserNick() != "")
        user.getServer()->removeNickList(user.getUserNick());
    std::cout<<"closing FD = " << user.getUserFd() << std::endl;
    close(user.getUserFd());
    // delete user;
}