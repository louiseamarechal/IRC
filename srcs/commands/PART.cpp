/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:12 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:50:13 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void    partChannel(std::string params, User &user)
{
    std::string                 channelName;
    std::string                 partMessage = "";
    std::vector<std::string>    splittedParams;
    std::string                 errorMessage;
    std::string                 rpl;

    if (user.getIsUserRegistered() == false)
    {
        errorMessage = sendMessage(451, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (params.empty())
    {
        errorMessage = sendMessage1(461, user, *user.getServer(), "PART");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    splittedParams = splitString(removeConsecutiveWhitespace(params));
    channelName = splittedParams[0];
    std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();

    if (splittedParams.size() > 1)
        partMessage = createMessage(splittedParams);

    rpl = ":" + user.getUserNick() + irssi + " PART " + channelName + " " + partMessage + "\r\n";

    if (user.getServer()->channels[channelName] == NULL) // channel n'existe pas
    {
        errorMessage = sendMessage1(403, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (user.getChannelName() != channelName) // user not in this channel
    {
        errorMessage = sendMessage1(442, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (user.getUserChannel().getChannelMembers().size() > 1)
        user.getUserChannel().sendMessageToEveryone(rpl, user.getUserFd());
    
    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    user.clearChannel(); // clear channelName + _userChannel pointe sur NULL
    user.getServer()->channels[channelName]->removeChannelMembers(user); // remove User de _channelMembers + delete le channel dans server
}

