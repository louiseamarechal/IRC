#include "commands.hpp"
#include "reply.hpp"


void    quit(std::string params, User &user)
{
    int fd = user.getUserFd();
    (void) params;
    if (user.getUserNick() != "")
        user.getServer()->removeNickList(user.getUserNick());
    else
        std::cout<< "cant find nickname " << std::endl;
    std::cout<<"closing FD = " << user.getUserFd() << std::endl;
    // close(user.getUserFd());
    user.getServer()->removeUser(user.getUserFd());
    close(fd);
    // delete user;
}