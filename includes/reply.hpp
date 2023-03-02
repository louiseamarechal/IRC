/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:48:20 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 14:06:46 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef REPLY_HPP
# define REPLY_HPP

#include "user/User.hpp"
#include "server/Server.hpp"
#include <sstream>
#include <ostream>

/************************************************/
/*                    RPL                       */
/************************************************/

/* 001 */ # define RPL_WELCOME(nick) (":Welcome to the Internet Relay Network " + nick + "\r\n")
/* 002 */ # define RPL_YOURHOST(servername, version) (":Your host is " + servername + ", running version " + version + "\r\n")
/* 003 */ # define RPL_CREATED(date) (":This server was created " + date + "\r\n")
/* 004 */ # define RPL_MYINFO(servername, version, userModes, channelModes) (servername + " " + version + " " + userModes + " " + channelModes + "\r\n")
/* 311 */ # define RPL_WHOISUSER(nick, user, host, real_name) (nick + " " + user + " " + host + " * :" + real_name + "\r\n")
/* 312 */ # define RPL_WHOISSERVER(nick, server, server_info) (nick + " " + server + " :<" + server_info + "\r\n")
/* 313 */ # define RPL_WHOISOPERATOR(nick) (nick + " :is an IRC operator \r\n")
/* 314 */ # define RPL_WHOWASUSER(nick, user, host, real_name) (nick + " " + user + " " + host + "  * :" + real_name + "\r\n")
/* 315 */ # define RPL_ENDOFWHO(name) (name + " :End of WHO list \r\n")
/* 317 */ # define RPL_WHOISIDLE(nick, integer) (nick + integer + " :seconds idle \r\n")
/* 318 */ # define RPL_ENDOFWHOIS(nick) (nick + " :End of WHOIS list \r\n")
/* 322 */ # define RPL_LIST()
/* 323 */ # define RPL_LISTEND() (":End of LIST\r\n")
/* 331 */ # define RPL_NOTOPIC(channel) (channel + ":No topic is set \r\n")
/* 332 */ # define RPL_TOPIC(channel, topic) (channel + " :" + topic + "\r\n")
/* 341 */ # define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n")
/* 353 */ # define RPL_NAMREPLY(channel, nickList) ("= " + channel + " :" + nickList + "\r\n")
/* 366 */ # define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list \r\n")
/* 369 */ # define RPL_ENDOFWHOWAS(nick) (nick + " :End of WHOWAS"+ "\r\n")
/* 372 */ # define RPL_MOTD(text) (":- " + text + "\r\n")
/* 375 */ # define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n")
/* 376 */ # define RPL_ENDOFMOTD() (":End of MOTD command\r\n")
/* 381 */ # define RPL_YOUREOPER() (" : You are now an IRC operator \r\n")
/* 392 */ # define RPL_USERSSTART() (":UserID Terminal Host \r\n")
/* 393 */ # define RPL_USERS(username, ttyline, hostname) (":" + username + " " + ttyline + " " + hostname + "\r\n")
/* 394 */ # define RPL_ENDOFUSERS() (":End of users \r\n")
/* 395 */ # define RPL_NOUSERS() (":Nobody logged in \r\n")

/************************************************/
/*                    ERR                       */
/************************************************/

/* 401 */ # define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel \r\n")
/* 402 */ # define ERR_NOSUCHSERVER(server_name) (server_name + " :No such server\r\n")
/* 403 */ # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel \r\n")
/* 404 */ # define ERR_CANNOTSENDTOCHAN(channel_name) (channel_name + " :Cannot send to channel \r\n")
/* 405 */ # define ERR_TOOMANYCHANNELS(channel_name) (channel_name + " :You have joined too many channels\r\n")
/* 406 */ # define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname \r\n")
/* 407 */ # define ERR_TOOMANYTARGETS(target) (target + " :" + " too many recipients. Please only send to 1 channel/user.\r\n")
/* 409 */ # define ERR_NOORIGIN() (":No origin specified \r\n")
/* 411 */ # define ERR_NORECIPIENT(command) (":No recipient given " + command + "\r\n")
/* 412 */ # define ERR_NOTEXTTOSEND() (":No text to send \r\n")
/* 413 */ # define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified \r\n")
/* 414 */ # define ERR_WILDTOPLEVEL(mask) (mask + " :Wildcard in toplevel domain \r\n")
/* 422 */ # define ERR_NOMOTD() (":MOTD File is missing \r\n")
/* 424 */ # define ERR_FILEERROR(file_operation, file) (":File error doing " + file_operation + " on " + file + "\r\n")
/* 431 */ # define ERR_NONICKNAMEGIVEN() (":No nickname given \r\n")
/* 432 */ # define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneous nickname\r\n")
/* 433 */ # define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use \r\n")
/* 437 */ # define ERR_UNAVAILRESOURCE(nick_channel) (nick_channel + " :Nick/channel is temporarily unavailable \r\n")
/* 441 */ # define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren’t on that channel\r\n")
/* 442 */ # define ERR_NOTONCHANNEL(channel) (channel + " :You’re not on that channel\r\n")
/* 443 */ # define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel \r\n")
/* 446 */ # define ERR_USERSDISABLED() (":USERS has been disabled \r\n")
/* 451 */ # define ERR_NOTREGISTERED() (":You have not registered \r\n")
/* 461 */ # define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters \r\n")
/* 462 */ # define ERR_ALREADYREGISTRED() (":Unauthorized command (already registered) \r\n")
/* 464 */ # define ERR_PASSWDMISMATCH() (":Password incorrect\r\n")
/* 471 */ # define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n")
/* 473 */ # define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)\r\n")
/* 474 */ # define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)\r\n")
/* 475 */ # define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)\r\n")
/* 476 */ # define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask \r\n")
/* 477 */ # define ERR_NOCHANMODES(channel) (channel + " :Channel doesn’t support modes\r\n")
/* 481 */ # define ERR_NOPRIVILEGES()(":Permission Denied- You're not an IRC operator\r\n")
/* 482 */ # define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You’re not channel operator\r\n")
/* 491 */ # define ERR_NOOPERHOST() (":No O-lines for your host \r\n")
/*     */ # define ERR_TOOMANYMATCHES() ()

class Server;
class User;

std::string     formatMessage(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4 );
std::string     sendMessage(int code, User &user, Server &server);
std::string     sendMessage1(int code, User &user, Server &server, std::string str1);
std::string     sendMessage2(int code, User &user, Server &server, std::string str1, std::string str2);
std::string     sendMessage3(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3);
std::string     sendMessage4(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4);
std::string     addPrefixToMotd(std::string text, std::string prefix);
void            sendWelcomeMessages(User& user, Server &server);

#endif