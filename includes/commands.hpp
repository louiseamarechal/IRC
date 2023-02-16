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
#include "channel/Channel.hpp"
#include "reply.hpp"
#include "utils.hpp"

class Channel;
class User;

void                    setNick(std::string nick, User &user);
void                    setUser(std::string params, User &user);
void                    checkPass(std::string password);
bool                    isNickformatok(std::string nick);
void                    motd(std::string params, User &user);

void                    joinChannel(std::string channelName, User &user);
void                    partChannel(std::string str, User &user);
void                    sendprivmsg(std::string message);


#endif