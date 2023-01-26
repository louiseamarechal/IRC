# ifndef COMMANDS_HPP
# define COMMANDS_HPP

// RPL
    // AFTER REGISTRATION
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n") // 001
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n") // 002
# define RPL_CREATED(date) (":This server was created " + date + "\r\n") // 003
# define RPL_MYINFO(servername, version, userModes, channelModes) (servername + " " + version + " " + userModes + " " + channelModes) // 004
    
    // JOIN
# define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") // 332

    // TOPIC
# define RPL_NOTOPIC(channel) (channel + ":No topic is set \r\n") // 331
// + RPL_TOPIC

    // NAMES
# define RPL_NAMREPLY() // 353
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list \r\n") // 366

    // LIST
# define RPL_LIST() // 322
# define RPL_LISTEND() (":End of LIST\r\n") // 323

    // INVITE
# define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n") // 341
// # define RPL_AWAY -> do wo use if we don't do MODE ?

    // PRIVMSG
// RPL_AWAY(nick, message) (nick + " :" + message + "\r\n") // 301

    // MOTD
# define RPL_MOTDSTART
# define RPL_ENDOFMOTD
# define RPL_MOTD

// ERR
    // USER + JOIN
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters \r\n") // 461
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered \r\n") // 462

    // NICK + JOIN
# define ERR_NONICKNAMEGIVEN() (":No nickname given \r\n") // 431
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use \r\n") // 433
# define ERR_UNAVAILRESOURCE(nick_channel) (nick_channel + " :Nick/channel is temporarily unavailable \r\n") // 437
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname \r\n") // 432
// # define ERR_NICKCOLLISION do we use ?
// # define ERR_RESTRICTED do we use ?

    //JOIN
# define ERR_INVITEONLYCHAN
# define ERR_CHANNELISFULL
# define ERR_NOSUCHCHANNEL
# define ERR_TOOMANYTARGETS
# define ERR_BANNEDFROMCHAN
# define ERR_BADCHANNELKEY
# define ERR_BADCHANMASK
# define ERR_TOOMANYCHANNELS
// + NEEDMOREPARAMS + UNAVAILABLE RESSOURSES

    // PART
# define ERR_NOTONCHANNEL
// + ERR_NEEDMOREPARAMS + ERR_NOSUCHCHANNEL

    // TOPIC
# define ERR_NOCHANMODES
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel \r\n") // 442
# define ERR_CHANOPRIVSNEEDED
// + ERR_NEEDMOREPARAMS + ERR_CHANOPRIVSNEEDED

    // NAMES
# define ERR_TOOMANYMATCHES
# define ERR_NOSUCHSERVER

    // LIST
// ERR_TOOMANYMATCHES + ERR_NOSUCHSERVER

    // INVITE
# define ERR_NOSUCHNICK
# define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel \r\n")
// ERR_NEEDMOREPARAMS + ERR_NOTONCHANNEL + ERR_CHANOPRIVSNEEDED

    // PRIVMSG
# define ERR_NORECIPIENT
# define ERR_CANNOTSENDTOCHAN
# define ERR_WILDTOPLEVEL
# define ERR_NOTEXTTOSEND
# define ERR_NOTOPLEVEL
# define ERR_TOOMANYTARGETS
// + ERR_NOSUCHNICK

    // MOTD
# define ERR_NOMOTD

    // OTHER
# define ERR_NOTREGISTERED() (":You have not registered \r\n") // 451
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered) \r\n") // 462

    // WHOIS
    // WHO
    // WHOWAS
    // PING
    // PONG
    // USERS

#endif