#include "commands.hpp"
#include "reply.hpp"

void    setNick(std::string nick, User &user)
{
    std::cout << "Set Nick -- nick = " << nick << std::endl;

   std::vector<std::string> nicklist = user.getServer()->getNickList();
   if (isNickformatok(nick) == false)
    {
        send(user.getUserFd(), sendMessage1(432, user, *(user.getServer()), nick).c_str(), sendMessage1(432, user, *(user.getServer()), nick).size(), 0);
        std::cout<<"NICKNAME == FALSE"<<std::endl;
        return;
    }
    if (user.getIsUserRegistered() == true)
    {
        if(std::find(nicklist.begin(), nicklist.end(), nick) != nicklist.end())
            send(user.getUserFd(), sendMessage1(433, user, *(user.getServer()), nick).c_str(), sendMessage1(433, user, *(user.getServer()), nick).size(), 0);
        else
        {
            std::string tmp  = ":" + user.getUserNick() + " NICK :" + nick + "\r\n";
            std::cout << "nickname will be changed" << std::endl;
            user.getServer()->removeNickList(user.getUserNick());
            std::cout<<"old nick removed"<<std::endl;
            user.getServer()->setNickList(nick);
            user.setUserNick(nick);
            std::cout<<"new nick set == "<<user.getUserNick()<< std::endl;
            send(user.getUserFd(), tmp.c_str(), tmp.size(),0);
            return;
        }
    }
    else
    {
        if(user.getIsNickSet() == false)
        {
            if(std::find(nicklist.begin(), nicklist.end(), nick) != nicklist.end())
            {
                send(user.getUserFd(), sendMessage1(433, user, *(user.getServer()), nick).c_str(), sendMessage1(433, user, *(user.getServer()), nick).size(), 0);
                return;
            }
            user.setIsNickSet(true);
            user.setUserNick(nick);
            user.getServer()->setNickList(nick);
            if (user.getIsUserSet() == true)
            { 
                user.setIsUserRegistered(true);
                sendWelcomeMessages(user, *user.getServer());
            }
        }
        else
            sendMessage(451, user, *user.getServer());
    }
}

bool    isNickformatok(std::string nick)
{
    if (nick.size() == 0)
        return(false);
    if (nick.size() > 9)
        return (false);
    if (nick.find_first_not_of("-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM") == std::string::npos)
        return(true);
    return (false);
}   