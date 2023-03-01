#include "commands.hpp"
#include "reply.hpp"

void ping(std::string params, User &user)
{
    std::string tmp  =  " PONG :" + params + "\r\n";
	if (params.size() == 0)
		sendMessage(409, user, *user.getServer());
	send(user.getUserFd(), tmp.c_str(), tmp.size(),0);
    
}
