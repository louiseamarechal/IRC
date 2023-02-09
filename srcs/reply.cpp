#include "reply.hpp"

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
    std::string RPL4 = sendMessage4(004, user, server, server.getServerName(), server.getVersion(), "userModesTBC", "channelModesTBC");

    send(user.getUserFd(), RPL1.c_str(), RPL1.size(), 0);
    send(user.getUserFd(), RPL2.c_str(), RPL2.size(), 0);
    send(user.getUserFd(), RPL3.c_str(), RPL3.size(), 0);
    send(user.getUserFd(), RPL4.c_str(), RPL4.size(), 0);
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
        // case 301:
        //     return (prefix +) 
        case 311:
            return (prefix + RPL_WHOISUSER(str1, str2, str3, str4));
            // return (prefix + RPL_WHOISUSER(nick, user, host, real_name));
        case 312:
            return (prefix + RPL_WHOISSERVER(str1, str2, str3));
            // return (prefix + RPL_WHOISSERVER(nick, server, server_info));
        case 313:
            return (prefix + RPL_WHOISOPERATOR(str1));
            // return (prefix + RPL_WHOISOPERATOR(nick));
        case 314:
            return (prefix + RPL_WHOWASUSER(str1, str2, str3, str4));
            // return (prefix + RPL_WHOWASUSER(nick, user, host, real_name));
        case 315:
            return (prefix + RPL_ENDOFWHO(str1));
            // return (prefix + RPL_ENDOFWHO(name));
        case 317:
            return (prefix + RPL_WHOISIDLE(str1, str2));
            // return (prefix + RPL_WHOISIDLE(nick, integer));
        case 318:
            return (prefix + RPL_ENDOFWHOIS(str1));
            // return (prefix + RPL_ENDOFWHOIS(nick));
        // case 319:
        //     return (prefix + RPL_WHOISCHANNELS(str1));
            // return (prefix + RPL_WHOISCHANNELS(nick));
        // case 322:
        //     return
        case 323:
            return (prefix + RPL_LISTEND());
        case 331:
            return (prefix + RPL_NOTOPIC(str1));
            // return (prefix + RPL_NOTOPIC(channel));
        case 332:
            return (prefix + RPL_TOPIC(str1, str2));
            // return (prefix + RPL_TOPIC(channel, topic));
        case 341:
            return (prefix + RPL_INVITING(str1, str2));
            // return (prefix + RPL_INVITING(channel, nick));
        // case 352:
        //     return (prefix + RPL_WHOREPLY())
        // case 353:
        //     return (prefix + RPL_NAMREPLY())
        case 366:
            return (prefix + RPL_ENDOFNAMES(str1));
            // return (prefix + RPL_ENDOFNAMES(channel));
        case 369:
            return (prefix + RPL_ENDOFWHOWAS(str1));
            // return (prefix + RPL_ENDOFWHOWAS(nick));
        case 372:
            return (prefix + RPL_ENDOFMOTD(str1));
            // return (prefix + RPL_ENDOFMOTD(text));
        case 375:
            return (prefix + RPL_MOTDSTART(str1));
            // return (prefix + RPL_MOTDSTART(server));
        case 376:
            return (prefix + RPL_MOTD());
        case 381:
            return (prefix + RPL_YOUREOPER());
        case 392:
            return (prefix + RPL_USERSSTART());
        case 393:
            return (prefix + RPL_USERS(str1, str2, str3));
            // return (prefix + RPL_USERS(username, ttyline, hostname));
        case 394:
            return (prefix + RPL_ENDOFUSERS());
        case 395:
            return (prefix + RPL_NOUSERS());
        case 401:
            return (prefix + ERR_NOSUCHNICK(str1));
            // return (prefix + ERR_NOSUCHNICK(nickname));
        case 402:
            return (prefix + ERR_NOSUCHSERVER(str1));
            // return (prefix + ERR_NOSUCHSERVER(server_name));
        case 403:
            return (prefix + ERR_NOSUCHCHANNEL(str1));
            // return (prefix + ERR_NOSUCHCHANNEL(channel_name));
        case 404:
            return (prefix + ERR_CANNOTSENDTOCHAN(str1));
            // return (prefix + ERR_CANNOTSENDTOCHAN(channel_name));
        case 405:
            return (prefix + ERR_TOOMANYCHANNELS(str1));
            // return (prefix + ERR_TOOMANYCHANNELS(channel_name));
        case 406:
            return (prefix + ERR_WASNOSUCHNICK(str1));
            // return (prefix + ERR_WASNOSUCHNICK(nickname));
        case 407:
            return (prefix + ERR_TOOMANYTARGETS(str1, str2, str3));
            // return (prefix + ERR_TOOMANYTARGETS(target, error_code, message));
        case 409:
            return (prefix + ERR_NOORIGIN());
        case 411:
            return (prefix + ERR_NORECIPIENT(str1));
            // return (prefix + ERR_NORECIPIENT(command));
        case 412:
            return (prefix + ERR_NOTEXTTOSEND());
        case 413:
            return (prefix + ERR_NOTOPLEVEL(str1));
            // return (prefix + ERR_NOTOPLEVEL(mask));
        case 414:
            return (prefix + ERR_WILDTOPLEVEL(str1));
            // return (prefix + ERR_WILDTOPLEVEL(mask));
        case 422:
            return (prefix + ERR_NOMOTD());
        // case 424:
        //     return (prefix + ERR_FILEERROR(file_operation, file));
        case 431:
            return (prefix + ERR_NONICKNAMEGIVEN());
        case 432:
            return (prefix + ERR_ERRONEUSNICKNAME(str1));
            // return (prefix + ERR_ERRONEUSNICKNAME(nick));
        case 433:
            return (prefix + ERR_NICKNAMEINUSE(str1));
            // return (prefix + ERR_NICKNAMEINUSE(nick));
        // case 436:
        //     return
        case 437:
            return (prefix + ERR_UNAVAILRESOURCE(str1));
            // return (prefix + ERR_UNAVAILRESOURCE(nick/channel));
        case 442:
            return (prefix + ERR_NOTONCHANNEL(str1));
            // return (prefix + ERR_NOTONCHANNEL(channel));
        case 443:
            return (prefix + ERR_USERONCHANNEL(str1, str2));
            // return (prefix + ERR_USERONCHANNEL(user, channel));
        case 446:
            return (prefix + ERR_USERSDISABLED());
        case 451:
            return (prefix + ERR_NOTREGISTERED());
        case 461:
            return (prefix + ERR_NEEDMOREPARAMS(str1));
            // return (prefix + ERR_NEEDMOREPARAMS(command));
        case 462:
            return (prefix + ERR_ALREADYREGISTRED());
        case 464:
            return (prefix + ERR_PASSWDMISMATCH());
        case 471:
            return (prefix + ERR_CHANNELISFULL(str1));
            // return (prefix + ERR_CHANNELISFULL(channel));
        case 473:
            return (prefix + ERR_INVITEONLYCHAN(str1));
            // return (prefix + ERR_INVITEONLYCHAN(channel));
        case 474:
            return (prefix + ERR_BANNEDFROMCHAN(str1));
            // return (prefix + ERR_BANNEDFROMCHAN(channel));
        case 475:
            return (prefix + ERR_BADCHANNELKEY(str1));
            // return (prefix + ERR_BADCHANNELKEY(channel));
        case 476:
            return (prefix + ERR_BADCHANMASK(str1));
            // return (prefix + ERR_BADCHANMASK(channel));
        case 477:
            return (prefix +  ERR_NOCHANMODES(str1));
            // return (prefix +  ERR_NOCHANMODES(channel));
        // case 484:
        //     return (prefix + ERR_RESTRICTED());
        case 491:
            return (prefix + ERR_NOOPERHOST());
    }

    return (NULL);
}