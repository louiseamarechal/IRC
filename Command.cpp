#include "Command.hpp"

std::string    formatMessage(int code, Server &server, User &user) {

    switch (code)
	{
		case 001:
			return RPL_WELCOME(user.getUserNick());
		case 002:
            return RPL_YOURHOST(server.getServerName(), server.getVersion());
        case 003:
            return RPL_CREATED(server.getCreationDate());
        case 004:
            return RPL_MYINFO(server.getServerName(), server.getVersion(), );
        // case 301:
        //     return 
        case 311:
            return RPL_WHOISUSER(nick, user, host, real_name);
        case 312:
            return RPL_WHOISSERVER(nick, server, server_info);
        case 313:
            return RPL_WHOISOPERATOR(nick);
        case 314:
            return RPL_WHOWASUSER(nick, user, host, real_name);
        case 315:
            return RPL_ENDOFWHO(name);
        case 317:
            return RPL_WHOISIDLE(nick, integer);
        case 318:
            return RPL_ENDOFWHOIS(nick);
        case 319:
            return RPL_WHOISCHANNELS(nick);
        // case 322:
        //     return
        case 323:
            return RPL_LISTEND();
        case 331:
            return RPL_NOTOPIC(channel);
        case 332:
            return RPL_TOPIC(channel, topic);
        case 341:
            return RPL_INVITING(channel, nick);
        // case 352:
        //     return RPL_WHOREPLY()
        // case 353:
        //     return RPL_NAMREPLY()
        case 366:
            return RPL_ENDOFNAMES(channel);
        case 369:
            return RPL_ENDOFWHOWAS(nick);
        case 372:
            return RPL_ENDOFMOTD(text);
        case 375:
            return RPL_MOTDSTART(server);
        case 376:
            return RPL_MOTD();
        case 381:
            return RPL_YOUREOPER();
        case 392:
            return RPL_USERSSTART();
        case 393:
            return RPL_USERS(username, ttyline, hostname);
        case 394:
            return RPL_ENDOFUSERS();
        case 395:
            return RPL_NOUSERS();
        case 401:
            return ERR_NOSUCHNICK(nickname);
        case 402:
            return ERR_NOSUCHSERVER(server_name);
        case 403:
            return ERR_NOSUCHCHANNEL(channel_name);
        case 404:
            return ERR_CANNOTSENDTOCHAN(channel_name);
        case 405:
            return ERR_TOOMANYCHANNELS(channel_name);
        case 406:
            return ERR_WASNOSUCHNICK(nickname);
        case 407:
            return ERR_TOOMANYTARGETS(target, error_code, message);
        case 409:
            return ERR_NOORIGIN();
        case 411:
            return ERR_NORECIPIENT(command);
        case 412:
            return ERR_NOTEXTTOSEND();
        case 413:
            return ERR_NOTOPLEVEL(mask);
        case 414:
            return ERR_WILDTOPLEVEL(mask);
        case 422:
            return ERR_NOMOTD();
        case 424:
            return ERR_FILEERROR(file_operation, file);
        case 431:
            return ERR_NONICKNAMEGIVEN();
        case 432:
            return ERR_ERRONEUSNICKNAME(nick);
        case 433:
            return ERR_NICKNAMEINUSE(nick);
        // case 436:
        //     return
        case 437:
            return ERR_UNAVAILRESOURCE(nick_channel);
        case 442:
            return ERR_NOTONCHANNEL(channel);
        case 443:
            return ERR_USERONCHANNEL(user, channel);
        case 446:
            return ERR_USERSDISABLED();
        case 451:
            return ERR_NOTREGISTERED();
        case 461:
            return ERR_NEEDMOREPARAMS(command);
        case 462:
            return ERR_ALREADYREGISTRED();
        case 464:
            return ERR_PASSWDMISMATCH();
        case 471:
            return ERR_CHANNELISFULL(channel);
        case 473:
            return ERR_INVITEONLYCHAN(channel);
        case 474:
            return ERR_BANNEDFROMCHAN(channel);
        case 475:
            return ERR_BADCHANNELKEY(channel);
        case 476:
            return ERR_BADCHANMASK(channel);
        case 477:
            return  ERR_NOCHANMODES(channel);
        // case 484:
        //     return ERR_RESTRICTED();
        case 491:
            return ERR_NOOPERHOST();
}