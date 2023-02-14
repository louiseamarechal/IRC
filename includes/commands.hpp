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
#include "user/User.hpp"
#include "server/Server.hpp"
#include "reply.hpp"
#include "utils.hpp"


class User;

void                    setNick(std::string nick, User &user);
void                    setUser(std::string params, User &user);
void                    joinchannel(std::string join);
void                    checkPass(std::string password);
void                    sendprivmsg(std::string message);
bool                    isNickformatok(std::string nick);
void                    motd(std::string params, User &user);
void                    ping(std::string params, User &user);
void                    OPER(std::string params, User &user);

#endif