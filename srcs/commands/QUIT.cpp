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
    if (user.getUserNick().empty() == false)
        user.getServer()->removeNickList(user.getUserNick());
    std::cout<<"[QUIT] - closing FD = " << user.getUserFd() << std::endl;
    //  user.getServer()->removeUserWithFd(user.getUserFd());
     close(user.getUserFd());
   
    // delete user;
}