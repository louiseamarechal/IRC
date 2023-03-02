/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:27 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:49:30 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void  kill(std::string params, User& user)
{
std::vector<std::string> nicklist = user.getServer()->getNickList();

if (user.getIsOper() == false)
{
    send(user.getUserFd(),sendMessage(481, user, *user.getServer()).c_str(), sendMessage(481, user, *user.getServer()).size(),0);
    return;
}

if (params.size() == 0)
{
    send(user.getUserFd(),sendMessage1(461, user, *user.getServer(), "KILL").c_str(), sendMessage1(461, user, *user.getServer(), "KILL").size(), 0);
    return;
}

std::vector<std::string>    tmp = splitString(params);
std::string                 message;

if (tmp.size() < 2)
    send(user.getUserFd(), sendMessage1(461, user, *user.getServer(), "KILL").c_str(), sendMessage1(461, user, *user.getServer(), "KILL").size(), 0);
else
{
    message = createMessage(tmp);

    if (tmp[0] == user.getUserNick())
        return;

    if (std::find(nicklist.begin(), nicklist.end(), tmp[0]) == nicklist.end())
        send(user.getUserFd(), sendMessage1(401, user, *user.getServer(), tmp[0]).c_str(), sendMessage1(401, user, *user.getServer(), tmp[0]).size(), 0);
    else 
    {
        std::map<int, User*>    userMap = user.getServer()->getUserMap();

        for (std::map<int, User*>::iterator itMap = userMap.begin(); itMap != userMap.end(); itMap++)
        {
            if (tmp[0] == itMap->second->getUserNick())
            {
                std::string rpl = ":" + user.getUserNick() +  "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName() + " KILL " + tmp[0] + " " + message + "\r\n";
                send(itMap->first, rpl.c_str(), rpl.size(), 0);
                quit("", *itMap->second);
            }
        }
    }
}
}    
 
