/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:49:57 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "reply.hpp"

void    setNick(std::string nick, User &user)
{
    if (nick.empty() == true && user.getIsNickSet() == true)
    {
        std::string tmp = "Your nickname is : " + user.getUserNick() + "\n";
        send(user.getUserFd(), tmp.c_str(), tmp.size(), 0);
        return;
    }
   std::vector<std::string> nicklist = user.getServer()->getNickList();
   if (isNickformatok(nick) == false)
    {
        send(user.getUserFd(), sendMessage1(432, user, *(user.getServer()), nick).c_str(), sendMessage1(432, user, *(user.getServer()), nick).size(), 0);
        return;
    }
    if (user.getIsUserRegistered() == true)
    {
        if(std::find(nicklist.begin(), nicklist.end(), nick) != nicklist.end())
            send(user.getUserFd(), sendMessage1(433, user, *(user.getServer()), nick).c_str(), sendMessage1(433, user, *(user.getServer()), nick).size(), 0);
        else
        {
            std::string tmp  = ":" + user.getUserNick() + " NICK :" + nick + "\r\n";
            user.getServer()->removeNickList(user.getUserNick());
            user.getServer()->setNickList(nick);
            user.setUserNick(nick);
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