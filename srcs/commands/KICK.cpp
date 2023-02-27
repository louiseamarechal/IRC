#include "commands.hpp"

    // std::vector<std::string>::iterator  it;
    // std::string                         temp;

    // if (params.size() != 1)
    // {
    //     std::cout << "[KICK] - params.size() = " << params.size() << std::endl;
    //     for (it = params.begin(); it != params.end(); it++)
    //     {
    //         temp = *it;
    //         std::cout << "[KICK] - temp[temp.size() -1 ] == " << temp[temp.size() - 1] << std::endl;
    //         if (temp[temp.size() - 1] != ',' && (it)++ != params.end())
    //         {
    //             std::cout << "[KICK] - format not good !" << std::endl;
    //             return (false);
    //         }
    //     }
    // }
    // return (true);

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
        std::cout << "[KICK] - temp[temp.size() - 1] = " << temp[temp.size() - 1] << std::endl;
        if (temp[temp.size() - 1] != ',' && cmpt != vector.size())
        {
            std::cout << "[KICK] - comma with this bad boy : " << *it << std::endl;
            return (false);
        }
        if (temp[temp.size() - 1] == ',' && cmpt == vector.size())
        {
            std::cout << "[KICK] - comma with this bad boy : " << *it << std::endl;
            return (false);
        }
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
        errorMessage = sendMessage1(476, user, *(user.getServer()), *it); // ERR_NEEDMOREPARAMS
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return (false);
    }

    *channel += *it;
    // while (isChannel(*it) && it != params.end()) // tant que mon param commence par # || & je l'ajoute a mon vector channels
    // {
    //     (*channels).push_back(*it);
    //     it++;
    // }
    it++;
    std::cout << "[KICK] - (*it)[0] = " << (*it)[0] << std::endl;
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
        {
            std::cout << "[KICK] - I have Channels in the User list, wrong cmd format !" << std::endl;
            return (false);
        }
    }

    if (!goodCommaPlacement(*users) || (*channel)[(*channel).size() - 1] == ',') // verifier que , separe les differents channels et users
    {
        std::cout << "[KICK] - (*channel)[(*channel).size() - 1] == " << (*channel)[(*channel).size() - 1] << std::endl;
        return (false);
    }

    return (true);
}

void    kick( std::string params, User &user )
{
    std::vector<std::string>::iterator  it;
    std::vector< std::string >          splittedParams;
    std::vector< std::string >          users;
    std::string                         errorMessage;
    std::string                         comment;
    std::string                         channel;

    if (user.getIsUserRegistered() == false)
    {
        errorMessage = sendMessage(451, user, *(user.getServer())); // ERR_NOTREGISTERED
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (params.empty())
    {
        errorMessage = sendMessage1(461, user, *(user.getServer()), "KICK"); // ERR_NEEDMOREPARAMS
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    splittedParams = splitString(removeConsecutiveWhitespace(params));
    printVector(splittedParams, "Splitted Params");

    if (!spltiAndCheckParams(splittedParams, user, &channel, &users, &comment)) // check les virgules, l'ordre des parametres et le nb
    {
        std::cout << "[KICK] - Params Format not OK !" << std::endl;
        return;
    }

    // printVector(channels, "Channels");
    printVector(users, "Users");
    std::cout << "[KICK] - comment = " << comment << std::endl;

    if (!isInVectorList(channel, user.getServer()->getChannelNames()))
    {
        errorMessage = sendMessage1(403, user, *(user.getServer()), channel); // ERR_NOSUCHCHANNEL
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    if (user.getServer()->channels[channel]->getChannelOperator() != user.getUserNick())
    {
        errorMessage = sendMessage1(482, user, *(user.getServer()), channel); // ERR_NOSUCHCHANNEL// ERR_CHANOPRIVSNEEDED
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    std::vector<std::string>    nicklist = user.getServer()->getNickList();
    for (it = users.begin(); it != users.end(); it++)
    {
        if (std::find(nicklist.begin(), nicklist.end(), *it) == nicklist.end()) // si user existe pas
        {
            errorMessage = sendMessage2(441, user, *(user.getServer()), *it, channel);// ERR_USERNOTINCHANNEL
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
            return;
        }
        else if (user.getServer()->getUser(*it).getChannelName() != channel) // si user pas dans le channel
        {
            errorMessage = sendMessage2(441, user, *(user.getServer()), *it, channel);// ERR_USERNOTINCHANNEL
            send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
            return;
        }
    }

    if (user.getChannelName() != channel)
    {
        errorMessage = sendMessage1(442, user, *(user.getServer()), channel); //ERR_NOTONCHANNEL
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    std::map<int, User*>    userMap = user.getServer()->getUserMap();

    for (it = users.begin(); it != users.end(); it++)
    {
        for (std::map<int, User*>::iterator itMap = userMap.begin(); itMap != userMap.end(); itMap++)
        {
            if (*it == itMap->second->getUserNick())
            {
                itMap->second->clearChannel(); // clear channelName + _userChannel pointe sur NULL
                user.getServer()->channels[channel]->removeChannelMembers(*(itMap)->second);// remove User de _channelMembers + delete le channel dans server
            }
        }
    }
}
    // remove Chanel du User
    // 

    // check if params.empty() -> ERR_NEEDMOREPARAMS
    // divide the params with whitespaces as sep to get all the 
    // check that there is at least 1 channel and the list of users to kick
        // otherwise check that there is 1 channel per user 
    // check that the channel exists -> ERR_NOSUCHCHANNEL
    // check that the user using the cmd is OPER -> ERR_CHANOPRIVSNEEDED
    // chack that the user he wants to kick is in a channel -> ERR_USERNOTINCHANNEL
    // check that user asking to KICK is on channel -> ERR_NOTONCHANNEL

// ERR_NEEDMOREPARAMS
// ERR_BADCHANMASK
// ERR_USERNOTINCHANNEL
// ERR_NOSUCHCHANNEL
// ERR_CHANOPRIVSNEEDED
// ERR_NOTONCHANNEL