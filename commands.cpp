/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:10:56 by jbouyer           #+#    #+#             */
/*   Updated: 2023/01/30 15:54:19 by lmarecha         ###   ########.fr       */
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
            user.getServer().getNickList().push_back(nick);  //rajoutera la list de nick.
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
             user.getServer().getNickList().push_back(nick);
             if (user.getIsUserSet() == true)
                user.setIsUserRegistered(true);
        }
        // else
            // erreur ne peux pas modif car pas enregistre.
    }
    // else 
        //erreur car pas deja pris.
}

void    setUser(std::string params, User &user) {

    
}



bool    isNickDispo(std::string nick, User &User)
{
    //verif Format
    std::vector<std::string> malist = User.getServer().getNickList();
    if (nick.size() > 9)
        return (false); //et RPL correspondant ?;
    if (strspn( nick.c_str(), "-_qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM" ) == nick.size())
        return (true);
    else
        return (false);
    //verif si existe deja le meme.
    std::vector<std::string>::iterator it = malist.begin();
    while (it != malist.end())
    {
        if (nick == *it)
           return(false);
        it++;
    }
    return (true);
}   