/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:10:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/02/08 16:47:06 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "Server.hpp"
#include<vector>
#include "Reply.hpp"
#include <algorithm>
#include <iostream>       
#include <string>         
#include <cstddef>


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