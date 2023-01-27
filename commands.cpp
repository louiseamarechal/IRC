/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:10:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/01/27 15:36:46 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "Server.hpp"
#include<vector>

void    setNick(std::string nick, User &user)
{
    //si il est resgistered change juste le nick et fait la modif dans map de nick.
    if (user.getIsUserRegistered() == true)
    {
        if(isNickDispo(nick, user) == true)
        {
            // user.getServer()->getNickList().erase(user.getUserNick()); faire fonction qui enleve le nick
            user.getServer()->getNickList().push_back(nick);  //rajoutera la list de nick.
            user.setUserNick(nick);
        }
        // else
        //     RPL_ERROR // a voir exactement comment mettre l'erreur ! 
    }
    else if (isNickDispo(nick, user) == true)
    {
        if(user.getIsNickSet() == false)
        {
             user.setIsNickSet(true);
             user.setUserNick(nick);
             user.getServer()->getNickList().push_back(nick);
             if (user.getIsUserSet() == true)
                user.setIsUserRegistered(true);
        }
        else
            // erreur ne peux pas modif car pas enregistre.
    }
    // else 
        //erreur car pas deja pris.
}





bool    isNickDispo(std::string nick, User &User)
{
    //verif Format
    if (nick.size() > 9)
        return (false); //et RPL correspondant ?;
    if (strspn( nick.c_str(), "-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM" ) == nick.size())
        return (true);
    else
        return (false);
    //verif si existe deja le meme.
    std::vector<std::string>::iterator it = User.getServer()->getNickList().begin();
    while (it != User.getServer()->getNickList().end())
    {
        if (nick == *it)
           return(false);
        it++;
    }
    return (true);
}   