/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:10:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/02/07 13:12:20 by jbouyer          ###   ########.fr       */
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
   std::vector<std::string> nicklist = user.getServer().getNickList();
   if (isNickformatok(nick) == 1)
        send(user.getUserFd(), sendMessage1(432, user, user.getServer(), nick).c_str(), 60, 0);
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
    std::cout<<"nick size= "<< nick.size();
    if (nick.size() > 9)
        return (false);
    if (nick.find_first_not_of("-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM") == std::string::npos)
        return(true);
    std::cout << "retour de nick first " << nick.find_first_not_of("-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM\n")<< std::endl;
    std::cout<<std::string::npos<<std::endl;
    return (false);
}   

//rajouter les RPL si ca se passe bien aussi !

// void    SetUser(std::string buffer, User &user)
// {
//     std::string     fullName;
//     std::string     UserNick; //ici il faudra voir en cas de conflit lequel on priorise...
// }