/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:48:47 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 14:02:49 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel/Channel.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Channel::Channel( std::string name, Server& server, User& user ) : _channelMembers(std::vector<User*>()),
                                                                _server(server),
                                                                _channelOperator(&user), 
                                                                _channelCreator(&user)
{
    if ( channelNameFormatIsOk(name))
        _channelName = name;
    else
    {
        std::string errorMessage = sendMessage1(476, user, server, name);
        send(user.getUserFd(), errorMessage.c_str(), errorMessage.size(), 0);
        return;
    }

    std::cout << CYN << "[CHANNEL] - Channel created : " << CRESET << _channelName << std::endl;

    addChannelMembers(user);
    server.setChannels(this);

    return ;
}

Channel&    Channel::operator=( Channel const & rhs )
{
    if (this != &rhs)
    {
        _channelName = rhs.getChannelName();
        _channelMembers = rhs.getChannelMembers();
        _server = getChannelServer();
        _channelOperator = getChannelOperator();
        _channelCreator = getChannelCreator();
    }

    return (*this);
}

Channel::~Channel( void ) 
{ 
    std::cout << CYN << "[CHANNEL] - Destroying Channel : " << CRESET << _channelName << std::endl;
    return;
}

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

std::string         Channel::getChannelName( void ) const { return (_channelName); }
std::vector<User*>  Channel::getChannelMembers( void ) const { return (_channelMembers); }
User*               Channel::getChannelCreator( void ) const { return (_channelCreator); }
User*               Channel::getChannelOperator( void ) const { return (_channelOperator); }
Server&             Channel::getChannelServer( void ) const { return (_server); }

std::string         Channel::getAllMembersName( void ) const
{
    std::vector<User*>::const_iterator    it;
    std::string                     membersNames;


    for (it = _channelMembers.begin(); it != _channelMembers.end(); it++)
    {
        if (_channelOperator == NULL)
            membersNames += " ";
        else if ((*it)->getUserNick() == _channelOperator->getUserNick())
            membersNames += "@";
        else
            membersNames += " ";
        membersNames += (*it)->getUserNick();
        membersNames += " ";
    }
    
    return (membersNames);
}


/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

void    Channel::addChannelMembers( User& user )
{
    std::vector<User*>::iterator    it;
    std::string                     userNick = user.getUserNick();

    for (it = _channelMembers.begin(); it != _channelMembers.end(); it++)
    {
        if ((*it)->getUserNick() == userNick)
            return;
    }

    _channelMembers.push_back(&user);
    
    return;
}

void    Channel::sendMessageToEveryone( std::string buffer, int fd )
{
    std::vector<User*>::iterator    it = _channelMembers.begin();
    
    if (_channelMembers.size() > 1)
    {
        while (it != _channelMembers.end())
        {
            if ((*it)->getUserFd() != fd)
                send((*it)->getUserFd(), buffer.c_str(), buffer.size(), 0);
            it++;
        }
    }
}

void    Channel::removeChannelMembers( User& user )
{
    if (_channelMembers.size() == 1) // last member of the channel
    {
        _channelMembers.clear();
        _server.deleteChannel(this);
        return ;
    }
    
    std::vector<User*>::iterator    it = _channelMembers.begin();
    std::string                     userNick = user.getUserNick();

    if (_channelOperator != NULL && _channelOperator->getUserNick() == userNick)
        _channelOperator = NULL;

    if (_channelCreator != NULL && _channelCreator->getUserNick() == userNick)
        _channelCreator = NULL;

    while (it != _channelMembers.end())
    {
        if ((*it)->getUserNick() == userNick)
            it = _channelMembers.erase(it);
        else
            ++it;
    }
}

bool    channelNameFormatIsOk( std::string name )
{
    if ( name.length() > 200 || name.length() < 1 )
        return (false);
    if ( (name.find(',') != std::string::npos) || (name.find(7) != std::string::npos) || (name.find(' ') != std::string::npos))
        return (false);
    if (name[0] != '#' && name[0] != '&')
        return (false);
    
    return (true);
}