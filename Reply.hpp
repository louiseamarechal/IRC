# ifndef REPLY_HPP
# define REPLY_HPP

#include "User.hpp"
#include "Server.hpp"
#include <sstream>
#include <ostream>

/************************************************/
/*                    RPL                       */
/************************************************/

/* 001 */ # define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n")
/* 002 */ # define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n")
/* 003 */ # define RPL_CREATED(date) (":This server was created " + date + "\r\n")
/* 004 */ # define RPL_MYINFO(servername, version, userModes, channelModes) (servername + " " + version + " " + userModes + " " + channelModes + "\r\n")

/* 301 */ // RPL_AWAY(nick, message) (nick + " :" + message + "\r\n") // (PRIVMSG, INVITE, WHOIS)

/* 311 */ # define RPL_WHOISUSER(nick, user, host, real_name) (nick + " " + user + " " + host + " * :" + real_name + "\r\n") // (WHOIS)

/* 312 */ # define RPL_WHOISSERVER(nick, server, server_info) (nick + " " + server + " :<" + server_info + "\r\n") // (WHOIS, WHOWAS)
/* 313 */ # define RPL_WHOISOPERATOR(nick) (nick + " :is an IRC operator \r\n") // (WHOIS)
/* 314 */ # define RPL_WHOWASUSER(nick, user, host, real_name) (nick + " " + user + " " + host + "  * :" + real_name + "\r\n") // (WHOWAS)
/* 315 */ # define RPL_ENDOFWHO(name) (name + " :End of WHO list \r\n") // (WHO)
/* 317 */ # define RPL_WHOISIDLE(nick, integer) (nick + integer + " :seconds idle \r\n") // (WHOIS)
/* 318 */ # define RPL_ENDOFWHOIS(nick) (nick + " :End of WHOIS list \r\n") // (WHOIS)
// /* 319 */ # define RPL_WHOISCHANNELS(nick) (nick + " :*( ( "@" / "+" ) <channel> " " )\r\n") // (WHOIS) The ’@’ and ’+’ characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel

/* 322 */ # define RPL_LIST() //  (LIST)
/* 323 */ # define RPL_LISTEND() (":End of LIST\r\n") //  (LIST)

/* 331 */ # define RPL_NOTOPIC(channel) (channel + ":No topic is set \r\n") //  (TOPIC)

/* 332 */ # define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n") // (JOIN, TOPIC)

/* 341 */ # define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n") // (INVITE)

/* 352 */ // (a retravailler) # define RPL_WHOREPLY(channel, user, host, server, nick, hopcount, real_name) ("<channel> <user> <host> <server> <nick> ( "H" / "G" > ["*"] [ ( "@" / "+" ) ]:<hopcount> <real_name> \r\n") // (WHO)
/* 353 */ # define RPL_NAMREPLY() // (NAMES)
/* 366 */ # define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list \r\n") // (NAMES)
/* 369 */ # define RPL_ENDOFWHOWAS(nick) (nick + " :End of WHOWAS") // (WHOWAS)

/* 372 */ # define RPL_ENDOFMOTD(text) (":- " + text + "\r\n") // (MOTD)
/* 375 */ # define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n") // (MOTD)
/* 376 */ # define RPL_MOTD() (":End of MOTD command") // (MOTD)

/* 381 */ # define RPL_YOUREOPER() (":You are now an IRC operator \r\n") // (OPER)
/* 392 */ # define RPL_USERSSTART() (":UserID Terminal Host \r\n") // (USERS)
/* 393 */ # define RPL_USERS(username, ttyline, hostname) (":" + username + " " + ttyline + " " + hostname + "\r\n") // (USERS)
/* 394 */ # define RPL_ENDOFUSERS() (":End of users \r\n") // (USERS)
/* 395 */ # define RPL_NOUSERS() (":Nobody logged in \r\n") // (USERS)


/************************************************/
/*                    ERR                       */
/************************************************/

/* 401 */ # define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel \r\n") // (INVITE, PRIVMSG, WHOIS)
/* 402 */ # define ERR_NOSUCHSERVER(server_name) (server_name + " :No such server\r\n") // (NAMES, LIST, WHOIS, WHO, PING, PONG, USERS)
/* 403 */ # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel \r\n") // (JOIN, PART)
/* 404 */ # define ERR_CANNOTSENDTOCHAN(channel_name) (channel_name + " :Cannot send to channel \r\n") // (PRIVMSG)
/* 405 */ # define ERR_TOOMANYCHANNELS(channel_name) (channel_name + " :You have joined too many channels\r\n") // (JOIN)
/* 406 */ # define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname \r\n") // (WHOWAS)
/* 407 */ # define ERR_TOOMANYTARGETS(target, error_code, message) (target + " :" + error_code + " recipients. " + message + "\r\n") // (JOIN, PRIVMSG)

/* 409 */ # define ERR_NOORIGIN() (":No origin specified \r\n") // (PING, PONG) (- PING or PONG message missing the originator parameter.)

/* 411 */ # define ERR_NORECIPIENT(command) (":No recipient given " + command + "\r\n") // (PRIVMSG)
/* 412 */ # define ERR_NOTEXTTOSEND() (":No text to send \r\n") // (PRIVMSG)
/* 413 */ # define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified \r\n") // (PRIVMSG)
/* 414 */ # define ERR_WILDTOPLEVEL(mask) (mask + " :Wildcard in toplevel domain \r\n") // (PRIVMSG)

/* 422 */ # define ERR_NOMOTD() (":MOTD File is missing \r\n") // (MOTD)

/* 424 */ # define ERR_FILEERROR(file_operation, file) (":File error doing " + file_operation + " on " + file + "\r\n") // (USERS)

/* 431 */ # define ERR_NONICKNAMEGIVEN() (":No nickname given \r\n") // (NICK, WHOIS, WHOWAS)
/* 432 */ # define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname \r\n") // (NICK)
/* 433 */ # define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use \r\n") // (NICK)

/* 436 */ //# define ERR_NICKCOLLISION do we use ? // (NICK)
/* 437 */ # define ERR_UNAVAILRESOURCE(nick_channel) (nick_channel + " :Nick/channel is temporarily unavailable \r\n") // (NICK, JOIN)

/* 442 */ # define ERR_NOTONCHANNEL(channel) (channel + " :You’re not on that channel\r\n") // (PART, INVITE, TOPIC)
/* 443 */ # define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel \r\n") // (INVITE)

/* 446 */ # define ERR_USERSDISABLED() (":USERS has been disabled \r\n") // (USERS) A utiliser si la commande est desactivee

/* 451 */ # define ERR_NOTREGISTERED() (":You have not registered \r\n") // (OTHER)

/* 461 */ # define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters \r\n") // (USER, JOIN, PART, TOPIC, INVITE, OPER, PASS)
/* 462 */ # define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered \r\n") // (USER, PASS)

/* 464 */ # define ERR_PASSWDMISMATCH() (":Password incorrect \r\n") // (OPER)

/* 471 */ # define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n") // (JOIN)

/* 473 */ # define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n") // (JOIN)
/* 474 */ # define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n") // (JOIN)
/* 475 */ # define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n") // (JOIN)
/* 476 */ # define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask \r\n") // (JOIN)
/* 477 */ # define ERR_NOCHANMODES(channel) (channel + " :Channel doesn’t support modes\r\n") // (TOPIC)

/* 484 */ // # define ERR_RESTRICTED() (":Your connection is restricted! \r\n") // (mode +r) do we use ? // (NICK)

/* 491 */ # define ERR_NOOPERHOST() (":No O-lines for your host \r\n") // (OPER)

/**/ # define ERR_TOOMANYMATCHES() () // (NAMES, LIST)

class Server;
class User;

std::string    formatMessage(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4 );

std::string sendMessage(int code, User &user, Server &server);
std::string sendMessage1(int code, User &user, Server &server, std::string str1);
std::string sendMessage2(int code, User &user, Server &server, std::string str1, std::string str2);
std::string sendMessage3(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3);
std::string sendMessage4(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4);

#endif