/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:31 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:50:32 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "reply.hpp"


void    quit(std::string params, User &user)
{
    (void) params;
    if (user.getIsUserRegistered() == false)
    {
       close(user.getUserFd());
       return;
    }
    if (!user.getChannelName().empty())
        partChannel(user.getChannelName(), user);
    if (user.getUserNick().empty() == false)
        user.getServer()->removeNickList(user.getUserNick());
    close(user.getUserFd()); 
    user.getServer()->removeUserWithFd(user.getUserFd());
     
}