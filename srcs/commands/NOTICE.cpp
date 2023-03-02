/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:01 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:50:02 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

bool    isEverythingOkNotice( std::string params, User& user)
{
    std::vector<std::string> splittedBufer;
    std::string msgTarget;
    
    if (user.getIsUserRegistered() == false)
        return (false);
        
    if (params.empty())
        return (false);

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));

    if (splittedBufer.size() != 2 )
        return (false);

    msgTarget = splittedBufer[0];

    if (!isInVectorList(msgTarget, user.getServer()->getNickList()) && !isInVectorList(msgTarget, user.getServer()->getChannelNames())) // si user/channel n'existe pas
        return (false);

    if (splittedBufer[1].empty())
        return (false);

    return (true);
}

void    notice( std::string params, User& user )
{
    std::string msgTarget;
    std::string rpl;
    std::string irssi;
    std::vector<std::string> splittedBufer;

    if (!isEverythingOkNotice(params, user))
        return;

    splittedBufer = splitPrivmsgBuffer(removeConsecutiveWhitespace(params));
    msgTarget = splittedBufer[0];
    irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    rpl = ":" + user.getUserNick() + irssi + " NOTICE " + msgTarget + " :" + splittedBufer[1] + "\r\n"; 

    if (msgTarget[0] == '#' || msgTarget[0] == '&') // target = channel
    {
        if (user.getChannelName() != msgTarget)  // si user est pas dans ce channel
            return;
        user.getServer()->sendMessageToAllChannelMembers(rpl, user.getUserFd());
    }
    else
    {
        const User&   userTarget = user.getServer()->getUser(msgTarget);

        user.getServer()->sendPrivMessages(rpl, user.getUserFd(), userTarget.getUserFd());
    }
}