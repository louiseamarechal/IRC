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
            send(user.getUserFd(), sendMessage1(433, user, *(user.getServer()), nick).c_str(), 60, 0);
        else
        {
            std::cout << "nickname will be changed" << std::endl;
            user.getServer()->removeNickList(user.getUserNick());
            std::cout<<"old nick removed"<<std::endl;
            user.getServer()->setNickList(nick);
            user.setUserNick(nick);
            std::cout<<"new nick set == "<<user.getUserNick()<< std::endl;
            return;
            // std::vector<std::string>::iterator it = std::find(user.getServer()->getNickList().begin(), user.getServer()->getNickList().end(), user.getUserNick());
            // std::cout<<"premier element de nicklist"<< user.getServer()->getNickList()[0]<<std::endl;
            // std::cout<< "I found the last nick in place == " << *it << std::endl;
            // std::vector<std::string>::iterator it = find(user.getServer()->getNickList().begin(), user.getServer()->getNickList().end(), user.getUserNick());
            // // erase(user.getServer()->getNickList.at(find(nicklist.begin(), nicklist.end(), user.getUserNick())));
            // std::cout<<"it == "<< *it <<std::endl;
            // // nicklist.erase(it);
            // (void) it;
            // user.getServer()->getNickList().push_back(nick);
            
        }
    }
    else
    {
        if(user.getIsNickSet() == false)
        {
            user.setIsNickSet(true);
            user.setUserNick(nick);
            user.getServer()->setNickList(nick);
            std::cout << "nick push to nicklist" << std::endl;
            std::cout << "nicklist size" <<  user.getServer()->getNickList().size() << std::endl;
            // std::cout << "nicklist first element = " <<   user.getServer()->getNickList()[0] << std::endl;
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
    if (nick.size() > 9)
        return (false);
    if (nick.find_first_not_of("-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM") == std::string::npos)
        return(true);
    return (false);
}   