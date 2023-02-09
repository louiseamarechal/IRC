#include "commands.hpp"

void    setUser(std::string params, User &user)
{
    // std::string                 mode; // le mettre sistematiquement a 0 ?
    // std::string                 unused; // sert a rien
    std::string                 realname;
    std::string                 formattedParams;
    std::vector<std::string>    splittedParams;
    std::string                 errorMessage;

    if (user.getIsUserRegistered() == true)
    {
        errorMessage = sendMessage(462, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }
    
    formattedParams = removeConsecutiveWhitespace(params);
    splittedParams = splitString(formattedParams);
     
    if (splittedParams.size() < 4)
    {
        errorMessage = sendMessage1(461, user, *(user.getServer()), "USER");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }
    
    if (splittedParams[3][0] != ':')
        return;
        
    if (splittedParams.size() == 4)
        user.setUserFullName(splittedParams[3]);
    else if (splittedParams.size() > 4 )
    {
        realname.clear();
        for (unsigned long int i = 3; i < splittedParams.size(); i++)
        {
            realname.append(splittedParams[i]);
            realname += " ";
        }
        realname.erase(realname.size() - 1);
        user.setUserFullName(realname);
    }
       
    user.setUserLoggin(splittedParams[0]);
    user.setIsUserSet(true);
    
    if (user.getIsUserRegistered() == true)
        sendWelcomeMessages(user, *(user.getServer()));
    
    // mode = splittedParams[1];
    // unused = splittedParams[2];
}