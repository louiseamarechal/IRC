/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:53:13 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:56:18 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"

std::string     addPrefixToMotd(std::string text, std::string prefix) {
    
    std::string             newText;
    std::string::iterator   it;

    prefix += ":- ";

    for (it = text.begin(); it != text.end(); it++)
    {
        newText += *it;
        if (*it == '\n')
            newText += prefix;
    }

    return (newText);
}

std::string     sendMessage(int code, User &user, Server &server) {
    return (formatMessage(code, user, server, "", "", "", ""));
}

std::string     sendMessage1(int code, User &user, Server &server, std::string str1) {
    return (formatMessage(code, user, server, str1, "", "", ""));
}

std::string     sendMessage2(int code, User &user, Server &server, std::string str1, std::string str2) {
    return (formatMessage(code, user, server, str1, str2, "", ""));
}

std::string     sendMessage3(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3) {
    return (formatMessage(code, user, server, str1, str2, str3, ""));
}

std::string     sendMessage4(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4) {
    return (formatMessage(code, user, server, str1, str2, str3, str4));
}

void            sendWelcomeMessages(User& user, Server &server) {
    
    std::string RPL1 = sendMessage1(001, user, server, user.getUserNick());
    std::string RPL2 = sendMessage2(002, user, server, server.getServerName(), server.getVersion());
    std::string RPL3 = sendMessage1(003, user, server, server.getCreationDate());
    std::string RPL4 = sendMessage4(004, user, server, server.getServerName(), server.getVersion(), "userModesTBC", "channelModes nmvt");

    send(user.getUserFd(), RPL1.c_str(), RPL1.size(), 0);
    send(user.getUserFd(), RPL2.c_str(), RPL2.size(), 0);
    send(user.getUserFd(), RPL3.c_str(), RPL3.size(), 0);
    send(user.getUserFd(), RPL4.c_str(), RPL4.size(), 0);
    motd("", user);
}

std::string    formatMessage(int code, User &user, Server &server, std::string str1, std::string str2, std::string str3, std::string str4 ) {

    std::stringstream tempStr;
    tempStr << code;
    std::string strCode = tempStr.str();
    std::string nickName = user.getUserNick();
    std::string prefix;

    if (nickName.empty() == true)
        nickName = "*";

    if (code < 10)
        prefix = ":" + server.getServerName() + " " + "00" + strCode + " " + nickName + " "; // :JLA.irc.fr 001 :Welcome....
    else
        prefix = ":" + server.getServerName() + " " + strCode + " " + nickName + " "; // :JLA.irc.fr 001 :Welcome....

    switch (code)
	{
		case 1:
			return (prefix + RPL_WELCOME(str1));
		case 2:
            return (prefix + RPL_YOURHOST(str1, str2));
        case 3:
            return (prefix + RPL_CREATED(str1));
        case 4:
            return (prefix + RPL_MYINFO(str1, str2, str3, str4));
        case 311:
            return (prefix + RPL_WHOISUSER(str1, str2, str3, str4));
        case 312:
            return (prefix + RPL_WHOISSERVER(str1, str2, str3));
        case 313:
            return (prefix + RPL_WHOISOPERATOR(str1));
        case 314:
            return (prefix + RPL_WHOWASUSER(str1, str2, str3, str4));
        case 315:
            return (prefix + RPL_ENDOFWHO(str1));
        case 317:
            return (prefix + RPL_WHOISIDLE(str1, str2));
        case 318:
            return (prefix + RPL_ENDOFWHOIS(str1));
        case 323:
            return (prefix + RPL_LISTEND());
        case 331:
            return (prefix + RPL_NOTOPIC(str1));
        case 332:
            return (prefix + RPL_TOPIC(str1, str2));
        case 341:
            return (prefix + RPL_INVITING(str1, str2));
        case 353:
            return (prefix + RPL_NAMREPLY(str1, str2));
        case 366:
            return (prefix + RPL_ENDOFNAMES(str1));
        case 369:
            return (prefix + RPL_ENDOFWHOWAS(str1));
        case 372:
        {
            std::string texte = addPrefixToMotd(str1, prefix);
            return (prefix + RPL_MOTD(texte));
        }
        case 375:
            return (prefix + RPL_MOTDSTART(str1));
        case 376:
            return (prefix + RPL_ENDOFMOTD());
        case 381:
            return (prefix + RPL_YOUREOPER());
        case 392:
            return (prefix + RPL_USERSSTART());
        case 393:
            return (prefix + RPL_USERS(str1, str2, str3));
        case 394:
            return (prefix + RPL_ENDOFUSERS());
        case 395:
            return (prefix + RPL_NOUSERS());
        case 401:
            return (prefix + ERR_NOSUCHNICK(str1));
        case 402:
            return (prefix + ERR_NOSUCHSERVER(str1));
        case 403:
            return (prefix + ERR_NOSUCHCHANNEL(str1));
        case 404:
            return (prefix + ERR_CANNOTSENDTOCHAN(str1));
        case 405:
            return (prefix + ERR_TOOMANYCHANNELS(str1));
        case 406:
            return (prefix + ERR_WASNOSUCHNICK(str1));
        case 407:
            return (prefix + ERR_TOOMANYTARGETS(str1));
        case 409:
            return (prefix + ERR_NOORIGIN());
        case 411:
            return (prefix + ERR_NORECIPIENT(str1));
        case 412:
            return (prefix + ERR_NOTEXTTOSEND());
        case 413:
            return (prefix + ERR_NOTOPLEVEL(str1));
        case 414:
            return (prefix + ERR_WILDTOPLEVEL(str1));
        case 422:
            return (prefix + ERR_NOMOTD());
        case 431:
            return (prefix + ERR_NONICKNAMEGIVEN());
        case 432:
            return (prefix + ERR_ERRONEUSNICKNAME(str1));
        case 433:
            return (prefix + ERR_NICKNAMEINUSE(str1));
        case 437:
            return (prefix + ERR_UNAVAILRESOURCE(str1));
        case 441:
            return (prefix + ERR_USERNOTINCHANNEL(str1, str2));
        case 442:
            return (prefix + ERR_NOTONCHANNEL(str1));
        case 443:
            return (prefix + ERR_USERONCHANNEL(str1, str2));
        case 446:
            return (prefix + ERR_USERSDISABLED());
        case 451:
            return (prefix + ERR_NOTREGISTERED());
        case 461:
            return (prefix + ERR_NEEDMOREPARAMS(str1));
        case 462:
            return (prefix + ERR_ALREADYREGISTRED());
        case 464:
            return (prefix + ERR_PASSWDMISMATCH());
        case 471:
            return (prefix + ERR_CHANNELISFULL(str1));
        case 473:
            return (prefix + ERR_INVITEONLYCHAN(str1));
        case 474:
            return (prefix + ERR_BANNEDFROMCHAN(str1));
        case 475:
            return (prefix + ERR_BADCHANNELKEY(str1));
        case 476:
            return (prefix + ERR_BADCHANMASK(str1));
        case 477:
            return (prefix +  ERR_NOCHANMODES(str1));
        case 481:
            return (prefix + ERR_NOPRIVILEGES());
        case 482:
            return (prefix + ERR_CHANOPRIVSNEEDED(str1));
        case 491:
            return (prefix + ERR_NOOPERHOST());
    }

    return (NULL);
}