#include "commands.hpp"

// penser a verifier si ca existe deja ou pas comme surnom c'est mieux ...
void    setNick(std::string nick, User &user)
{
    std::cout << "Set Nick -- nick = " << nick << std::endl;

   std::vector<std::string> nicklist = user.getServer()->getNickList();
   if (isNickformatok(nick) == false)
        {send(user.getUserFd(), sendMessage1(432, user, *(user.getServer()), nick).c_str(), 60, 0);
        std::cout<<"NICKNAME == FALSE"<<std::endl;}
    if (user.getIsUserRegistered() == true)
    {
        if(std::find(nicklist.begin(), nicklist.end(), nick) != nicklist.end())
            send(user.getUserFd(), sendMessage1(433, user, *(user.getServer()), nick).c_str(), 60, 0); //plus tard formater le message
        else
        {
            std::vector<std::string>::iterator it = find(nicklist.begin(), nicklist.end(), user.getUserNick());
            nicklist.erase(it);
            nicklist.push_back(nick);
            user.setUserNick(nick);
        }
    }
    else
    {
        if(user.getIsNickSet() == false)
        {
            user.setIsNickSet(true);
            user.setUserNick(nick);
            nicklist.push_back(nick);
            if (user.getIsUserSet() == true)
            { 
                user.setIsUserRegistered(true);
                // RPLWELCOME + 4 messages distincts.
            }
        }
        // else
        //     return (451  define ERR_NOTREGISTERED)
    }
}

bool    isNickformatok(std::string nick)
{
    std::cout<<"nick = "<< nick;
    if (nick.size() > 9)
        return (false);
    if (nick.find_first_not_of("-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM") == std::string::npos)
        return(true);
    return (false);
}   