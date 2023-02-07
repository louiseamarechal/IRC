/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:58:26 by jbouyer           #+#    #+#             */
/*   Updated: 2023/02/07 14:11:41 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include "Server.hpp"
#include "User.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include "Reply.hpp"


class User;

void                    setNick(std::string nick, User &user);
void                    setUser(std::string params, User &user);
void                    joinchannel(std::string join);
void                    checkPass(std::string password);
void                    sendprivmsg(std::string message);
bool                    isNickformatok(std::string nick);

#endif