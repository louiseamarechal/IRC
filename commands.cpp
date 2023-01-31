/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:10:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/01/31 14:56:52 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "Server.hpp"
#include<vector>
#include "Reply.hpp"
#include <algorithm>



void    setNick(std::string nick, User &user)
{
   std::vector<std::string> nicklist = user.getServer().getNickList();
   if (isNickformatok(nick) == 1)
        send(user.getUserFd(), sendMessage1(432, user, user.getServer(), nick).c_str(), 60, 0);
    if (user.getIsUserRegistered() == true)
    {
        if(std::find(nicklist.begin(), nicklist.end(), nick) != nicklist.end())
            send(user.getUserFd(), sendMessage1(433, user, user.getServer(), nick).c_str(), 60, 0); //plus tard formater le message
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
    if (nick.size() > 9)
        return (false); //et RPL correspondant ?;
    if (strspn( nick.c_str(), "-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM" ) == nick.size())
        return (true);
    else
        return (false);
    return (true);
}   

//rajouter les RPL si ca se passe bien aussi !