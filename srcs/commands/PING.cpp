#include "commands.hpp"
#include "reply.hpp"


void ping(std::string params, User &user)
{
    std::cout<<"je suis dans PING"<<std::endl;
    std::string tmp  =  " PONG :" + params + "\r\n";
	if (params.size() == 0)
		sendMessage(409, user, *user.getServer());
    std::cout<<"response to PING sended" << std::endl;
	send(user.getUserFd(), tmp.c_str(), tmp.size(),0);
    
}
