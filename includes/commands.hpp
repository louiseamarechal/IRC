/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:48:09 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:48:12 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <exception>
#include "user/User.hpp"
#include "server/Server.hpp"
#include "channel/Channel.hpp"
#include "reply.hpp"
#include "utils.hpp"

class Channel;
class User;
class exception;

void                        setNick( std::string nick, User &user );
void                        setUser( std::string params, User &user );
void                        checkPass( std::string password );
bool                        isNickformatok( std::string nick );
void                        motd( std::string params, User &user );
void                        ping( std::string params, User &user );
void                        oper( std::string params, User &user );
void                        quit( std::string params, User &user );

void                        joinChannel( std::string channelName, User &user );
void                        partChannel( std::string str, User &user );
void                        sendPrivMsg( std::string msgTarget, User& user );
void                        names( std::string channelName, User &user );
void                        kick( std::string params, User &user );
void                        notice( std::string msgTarget, User& user );
void                        kill(std::string params, User& user);
std::vector<std::string>    splitPrivmsgBuffer( std::string params );

#endif