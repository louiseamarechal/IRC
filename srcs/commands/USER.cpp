/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:36 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:59:41 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void    setUser(std::string params, User &user)
{
    std::string                 realname;
    std::string                 formattedParams;
    std::vector<std::string>    splittedParams;
    std::string                 errorMessage;

    if (params.empty())
    {
        errorMessage = sendMessage1(461, user, *(user.getServer()), "USER");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (user.getIsUserRegistered() == true)
    {
        errorMessage = sendMessage(462, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }
    
    formattedParams = removeConsecutiveWhitespace(params);
    splittedParams = splitString(formattedParams);

    if (splittedParams.size() < 4 || (splittedParams[3].size() < 2 && splittedParams.size() == 4))
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
}