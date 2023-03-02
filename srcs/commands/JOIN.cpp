/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:04 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:49:06 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void    sendJoinRpl( User &user, std::string channelName )
{
    std::string irssi = "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName();
    std::string rpl = ":" + user.getUserNick() + irssi + " JOIN " + channelName + "\r\n";

    if (user.getUserChannel().getChannelMembers().size() > 1)
        user.getUserChannel().sendMessageToEveryone(rpl, user.getUserFd());

    send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
    names(channelName, user);
}

void    joinChannel( std::string params, User &user )
{
    std::string errorMessage;
    std::string channelName;

    if (!user.getIsUserRegistered())
    {
        errorMessage = sendMessage(451, user, *(user.getServer()));
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }   

    if (params.empty())
    {
        errorMessage = sendMessage1(461, user, *user.getServer(), "JOIN");
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    channelName = removeConsecutiveWhitespace(params);

    // si le user fait deja parti d'un channel
    if (!(user.getChannelName().empty()))
    {
        errorMessage = sendMessage1(405, user, *user.getServer(), channelName);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if ( user.getServer()->channels[channelName] == NULL )// si le channel n'existe pas encore
    {
        if (!channelNameFormatIsOk(channelName))
        {
            errorMessage = sendMessage1(476, user, *user.getServer(), channelName);
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
            return;
        }
        Channel  *newChannel = new Channel(channelName, *user.getServer(), user);

        // ajouter le channel a userChannel (il est ajoute a _channelMembers dans le constructeur + designe as channelOperator & channelCreator)
        user.setUserChannel(newChannel);

        //ajouter le Channel a la plublic map du server channels
        user.getServer()->setChannels(newChannel);
        sendJoinRpl(user, channelName);
        return;
    }
    
    // si le Channel existe et que User n'est pas deja dans un autre channel
    else if ((user.getServer()->channelIsOkToJoin(*user.getServer()->channels[channelName]) && user.getChannelName().empty()))
    {
    // add channel object to user
        user.setUserChannel(user.getServer()->channels[channelName]);
    
    // si user not already in _channelMembers list on l'y ajoute
        user.getServer()->channels[channelName]->addChannelMembers(user);
        sendJoinRpl(user, channelName);
    }
}