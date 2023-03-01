
#include "commands.hpp"
#include "reply.hpp"
#include "utils.hpp"
#include <cstring>

void oper(std::string params, User &user)
{
    std::vector<std::string> tmp;
    std::string operuser = "lol";
    std::string password = "mdr";

    if (!user.getIsUserRegistered())
    {
        std::string errorMessage = sendMessage(451, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }   
    if (params.size() == 0)
        send(user.getUserFd(),sendMessage1(461, user, *user.getServer(), "OPER").c_str(), sendMessage1(461, user, *user.getServer(), "OPER").size(), 0);
    else 
    {
        tmp = splitString(params);
        if (tmp.size() < 2)
            send(user.getUserFd(), sendMessage1(461, user, *user.getServer(), "OPER").c_str(), sendMessage1(461, user, *user.getServer(), "OPER").size(), 0);
        if (tmp[0] != "lol") 
            send(user.getUserFd(),sendMessage(464, user, *user.getServer()).c_str(), sendMessage(464, user, *user.getServer()).size(), 0);
        else if (tmp[1] != "mdr")
            send(user.getUserFd(),sendMessage(464, user, *user.getServer()).c_str(), sendMessage(464, user, *user.getServer()).size(), 0);
        else
        {
            user.setOper(true);
            send(user.getUserFd(), sendMessage(381, user, *user.getServer()).c_str(), sendMessage(381, user, *user.getServer()).size(), 0);
        }
    }
}

