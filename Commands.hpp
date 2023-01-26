# ifndef COMMANDS_HPP
# define COMMANDS_HPP

// RPL
    // AFTER REGISTRATION
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n") // 001
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n") // 002
# define RPL_CREATED(date) (":This server was created " + date + "\r\n") // 003
# define RPL_MYINFO(servername, version, userModes, channelModes) (servername + " " + version + " " + userModes + " " + channelModes) // 004

// RPL_AWAY(nick, message) (nick + " :" + message + "\r\n") // 301 (PRIVMSG, INVITE)

# define RPL_LIST() // 322 (LIST)
# define RPL_LISTEND() (":End of LIST\r\n") // 323 (LIST)

# define RPL_NOTOPIC(channel) (channel + ":No topic is set \r\n") // 331 (TOPIC)

# define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") // 332 (JOIN, TOPIC)

# define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n") // 341 (INVITE)

# define RPL_NAMREPLY() // 353 (NAMES)
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list \r\n") // 366 (NAMES)

# define RPL_ENDOFMOTD(text) (":- " + text + "\r\n") // 372 (MOTD)
# define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n") // 375 (MOTD)
# define RPL_MOTD() (":End of MOTD command") // 376 (MOTD)


// ERR
# define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel \r\n") // 401 (INVITE, PRIVMSG)
# define ERR_NOSUCHSERVER(server_name) (server_name + " :No such server\r\n") // 402 (NAMES, LIST)
# define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel \r\n") // 403 (JOIN, PART)
# define ERR_CANNOTSENDTOCHAN(channel_name) (channel_name + " :Cannot send to channel \r\n") // 404 (PRIVMSG)
# define ERR_TOOMANYCHANNELS(channel_name) (channel_name + " :You have joined too many channels\r\n") // 405 (JOIN)
# define ERR_TOOMANYTARGETS(target, error_code, message) (target + " :" + error_code + " recipients. " + message + "\r\n") //407 (JOIN, PRIVMSG)
# define ERR_NORECIPIENT(command) (":No recipient given " + command + "\r\n") // 411 (PRIVMSG)
# define ERR_NOTEXTTOSEND() (":No text to send \r\n") // 412 (PRIVMSG)
# define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified \r\n") // 413 (PRIVMSG)
# define ERR_WILDTOPLEVEL(mask) (maks + " :Wildcard in toplevel domain \r\n") // 414 (PRIVMSG)
# define ERR_NOMOTD() (":MOTD File is missing \r\n") // 422 (MOTD)

# define ERR_NONICKNAMEGIVEN() (":No nickname given \r\n") // 431 (NICK)
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname \r\n") // 432 (NICK)
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use \r\n") // 433 (NICK)
# define ERR_UNAVAILRESOURCE(nick_channel) (nick_channel + " :Nick/channel is temporarily unavailable \r\n") // 437 (NICK, JOIN)
// # define ERR_NICKCOLLISION do we use ? // 436 (NICK)

# define ERR_NOTONCHANNEL(channel) (channel + " :You’re not on that channel\r\n") // 442 (PART, INVITE, TOPIC)
# define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel \r\n") // 443 (INVITE)

# define ERR_NOTREGISTERED() (":You have not registered \r\n") // 451 (OTHER)
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters \r\n") // 461 (USER, JOIN, PART, TOPIC, INVITE)
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered \r\n") // 462 (USER)

# define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n") // 471 (JOIN)
# define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n") // 473 (JOIN)
# define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n") // 474 (JOIN)
# define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n") // 475 (JOIN)
# define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask \r\n") // 476 (JOIN)
# define ERR_NOCHANMODES(channel) (channel + " :Channel doesn’t support modes\r\n") // 477 (TOPIC)
# define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You’re not channel operator") // 482 (TOPIC, INVITE)

// # define ERR_RESTRICTED() (":Your connection is restricted! \r\n") // (mode +r) do we use ? // 484 (NICK)




# define ERR_TOOMANYMATCHES() () // (NAMES, LIST)





    // WHOIS
    // WHO
    // WHOWAS
    // PING
    // PONG
    // USERS

#endif