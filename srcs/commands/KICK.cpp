/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:49:16 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:49:20 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

static void sendErrorMessage(int code, User& user, std::string str1, std::string str2)
{
    std::string errorMessage;

    if (str1.empty() && str2.empty())
        errorMessage = sendMessage(code, user, *(user.getServer()));
    else if (str2.empty())
        errorMessage = sendMessage1(code, user, *(user.getServer()), str1);
    else
        errorMessage = sendMessage2(code, user, *(user.getServer()), str1, str2);

    send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
}

static bool isChannel(std::string param)
{
    if (param[0] == '#' || param[0] == '&')
        return (true);
    
    return (false);
} 

static bool goodCommaPlacement(std::vector<std::string> vector)
{
    std::vector<std::string>::iterator  it;
    std::string                         temp;
    size_t                              cmpt = 1;
    
    if (vector.size() == 1)
        return (true);

    for (it = vector.begin(); it != vector.end(); it++)
    {
        temp = *it;
        if (temp[temp.size() - 1] != ',' && cmpt != vector.size())
            return (false);
        if (temp[temp.size() - 1] == ',' && cmpt == vector.size())
            return (false);
        temp.clear();
        cmpt++;
    }

    return (true);
}

static bool spltiAndCheckParams( std::vector<std::string> params, User& user, std::string *channel, std::vector<std::string> *users, std::string *comment)
{
    std::vector<std::string>::iterator  it = params.begin();
    std::string                         errorMessage;

    if (!isChannel(*it))
    {
        sendErrorMessage(476, user, *it, ""); // ERR_NEEDMOREPARAMS
        return (false);
    }

    *channel += *it;
    it++;
    while (it != params.end())
    {
        if ((*it)[0] == ':')
            break ;
        (*users).push_back(*it); // j'ajoute le reste des params au vector users
        it++;
    }

    if (it != params.end() && (*it)[0] == ':')
    {
        while(it != params.end())
        {
            *comment += *it;
            *comment += " ";
            it++;
        }
    }

    for (it = (*users).begin(); it != (*users).end(); it++)
    {
        if (isChannel(*it)) // si j'ai des channels dans mon vector users (donc que la commande a ete mal tapee au debut)
            return (false);
    }

    if (!goodCommaPlacement(*users) || (*channel)[(*channel).size() - 1] == ',') // verifier que , separe les differents channels et users
        return (false);

    return (true);
}

void    kick( std::string params, User &user )
{
    std::vector<std::string>::iterator  it;
    std::vector< std::string >          splittedParams;
    std::vector< std::string >          users;
    std::string                         comment;
    std::string                         channel;

    if (user.getIsUserRegistered() == false)
    {
        sendErrorMessage(451, user, "", ""); // ERR_NOTREGISTERED
        return;
    }

    if (params.empty())
    {
        sendErrorMessage(461, user, "KICK", ""); // ERR_NEEDMOREPARAMS
        return;
    }

    splittedParams = splitString(removeConsecutiveWhitespace(params));

    if (!spltiAndCheckParams(splittedParams, user, &channel, &users, &comment)) // check les virgules, l'ordre des parametres et le nb
        return;

    for (it = users.begin(); it != users.end(); it++)
    {
        if (!((*it).empty()) && (*it)[(*it).size() - 1] == ',')
            (*it).erase((*it).size() - 1, 1);
    }

    if (!isInVectorList(channel, user.getServer()->getChannelNames()))
    {
        sendErrorMessage(403, user, channel, ""); // ERR_NOSUCHCHANNEL
        return;
    }

    if ((user.getServer()->channels[channel]->getChannelOperator() == NULL) || (user.getServer()->channels[channel]->getChannelOperator()->getUserNick() != user.getUserNick()))
    {
        sendErrorMessage(482, user, channel, ""); // ERR_NOSUCHCHANNEL// ERR_CHANOPRIVSNEEDED
        return;
    }

    std::vector<std::string>    nicklist = user.getServer()->getNickList();
    for (it = users.begin(); it != users.end(); it++)
    {
        if ((std::find(nicklist.begin(), nicklist.end(), *it) == nicklist.end()) || (user.getServer()->getUser(*it).getChannelName() != channel)) // si user existe pas
        {
            sendErrorMessage(441, user, *it, channel);// ERR_USERNOTINCHANNEL
            return;
        }

    }

    if (user.getChannelName() != channel)
    {
        sendErrorMessage(442, user, channel, ""); //ERR_NOTONCHANNEL
        return;
    }

    std::map<int, User*>    userMap = user.getServer()->getUserMap();
    std::string             rpl;

    for (it = users.begin(); it != users.end(); it++)
    {

        for (std::map<int, User*>::iterator itMap = userMap.begin(); itMap != userMap.end(); itMap++)
        {
            if (*it == user.getUserNick())
                return;
            if (*it == itMap->second->getUserNick())
            {
                rpl = ":" + user.getUserNick() +  "!" + user.getUserLoggin() + "@" + user.getServer()->getServerName() + " KICK " + channel + " " + *it + " " + comment + "\r\n";
                user.getServer()->sendMessageToAllChannelMembers(rpl, user.getUserFd());
                send(user.getUserFd(), rpl.c_str(), rpl.size(), 0);
                itMap->second->clearChannel(); // clear channelName + _userChannel pointe sur NULL
                user.getServer()->channels[channel]->removeChannelMembers(*(itMap)->second);// remove User de _channelMembers + delete le channel dans server
            }
        }
    }
}