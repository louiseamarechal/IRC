/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:16 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:50:17 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "reply.hpp"

void ping(std::string params, User &user)
{
    std::string tmp  =  ":" + user.getServer()->getServerName() + " PONG :" + params + "\r\n";
	if (params.size() == 0)
		tmp = sendMessage(409, user, *user.getServer());
	send(user.getUserFd(), tmp.c_str(), tmp.size(),0);
    
}
