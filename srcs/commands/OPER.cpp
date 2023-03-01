
#include "commands.hpp"
#include "reply.hpp"
#include "utils.hpp"
#include <cstring>

void oper(std::string params, User &user)
{
    std::vector<std::string> tmp;
    std::string operuser = "lol";
    std::string password = "mdr";

    if (params.size() == 0)
        sendMessage1(461, user, *user.getServer(), "OPER");
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

    //peut etre ajouter l'histoire de mode + 'o' si on a envie ?
}

