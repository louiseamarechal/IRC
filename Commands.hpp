# ifndef COMMANDS_HPP
# define COMMANDS_HPP

// RPL
# define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n") // 001
# define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n") // 002
# define RPL_CREATED(date) (":This server was created " + date + "\r\n") // 003
# define RPL_MYINFO(servername, version, userModes, channelModes) (servername + " " + version + " " + userModes + " " + channelModes) // 004

// ERR
    // USER
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters \r\n") // 461
# define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered \r\n") // 462

    // NICK
# define ERR_NONICKNAMEGIVEN() (":No nickname given \r\n") // 431
# define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use \r\n") // 433
# define ERR_UNAVAILRESOURCE
# define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname \r\n") // 432
// # define ERR_NICKCOLLISION do we use ?
// # define ERR_RESTRICTED do we use ?

#endif