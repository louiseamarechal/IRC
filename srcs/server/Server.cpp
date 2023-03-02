/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:44 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:59:24 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <algorithm>
#include <unistd.h>
#include "user/User.hpp"
#include "utils.hpp"
#include <sys/epoll.h>
#include <iostream>       
#include <string> 


/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Server::Server( void ) : _port(0),
                        _version("2.0"),
                        _serverName("JLA.irc.com"),
                        _password(""),
                        _creationDate("Wed Feb 8 15:53:25 2023"),
                        _maxUsers(100),
                        _serverFd(0),
                        _epollFd(0)

{
    _userMap = std::map<int, User*>();
    channels = std::map<std::string, Channel*>();
    _channelNames = std::vector<std::string>();
    _commandMap = std::map<std::string, void (*)(std::string, User &)>();

    _nickList = std::vector<std::string>();
    _nbUsers = 0;
    for (int i = 0; i < 200; i++) {
        _fds[i].fd = -1;
    }
    
    _commandMap["NICK"] = &setNick;
    _commandMap["USER"] = &setUser;
    _commandMap["USERHOST"] = &setUser;
    _commandMap["MOTD"] = &motd;
    _commandMap["JOIN"] = &joinChannel;
    _commandMap["PART"] = &partChannel;
    _commandMap["PING"] = &ping;
    _commandMap["OPER"] = &oper;
    _commandMap["QUIT"] = &quit;
    _commandMap["NAMES"] = &names;
    _commandMap["PRIVMSG"] = &sendPrivMsg;
    _commandMap["KICK"] = &kick;
    _commandMap["NOTICE"] = &notice;
    _commandMap["KILL"] = &kill;
    
    std::cout << MAG << "\n[SERVER CREATED]" << " - WELCOME TO JLA.IRC.COM -" << CRESET << std::endl;
    return ;
}

Server::~Server( void ) 
{ 
    std::cout << MAG << "\n[SERVER KILLED] - BYE, SEE YOU SOON -" << CRESET << std::endl;
    return ;
}

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

int                         Server::getPort() const { return (_port); }
std::string                 Server::getVersion() const { return (_version); }

int                         Server::getNbUsers() const { return (_nbUsers); }
int                         Server::getMaxUsers() const { return (_maxUsers); }

std::string                 Server::getServerName() const { return (_serverName); }

std::string                 Server::getPassword() const { return (_password); }

std::string                 Server::getCreationDate( void ) const { return (_creationDate); }

std::vector<std::string>    Server::getNickList() const { return (_nickList); }

std::vector<std::string>    Server::getChannelNames() const { return (_channelNames); }

const std::map< int, User* >&   Server::getUserMap( void ) const { return (_userMap); }

const   User&   Server::getUser( std::string nickName ) const
{
    std::map< int, User* >::const_iterator    it;
    
    for( it = _userMap.begin(); it != _userMap.end(); it++)
    {
        if ((*it).second->getUserNick() == nickName)
            return (*it->second);
    }

    throw (std::exception());
}

const std::map<std::string, void (*)(std::string params, User &user)>& Server::getCommandMap(void) const { return (_commandMap); }

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

void    Server::setPort( int port ) { _port = port; }

void    Server::setPassword( std::string password ) { _password = password; }

void    Server::setNickList(std::string nick)
{
    _nickList.push_back(nick);
}

void   Server::removeNickList(std::string oldNick)
{
    std::vector<std::string>::iterator it = std::find(_nickList.begin(), _nickList.end(), oldNick);
    if ( it != _nickList.end())
         _nickList.erase(it);
}

/*************************************************************************************/
/*                             CHANNEL FUNCTIONS                                     */
/*************************************************************************************/

void    Server::setChannels( Channel* channel )
{
    std::string channelName = channel->getChannelName();

    _channelNames.push_back(channelName);
    if (channels[channelName] == NULL)
        channels[channelName] = channel;
}


bool    Server::channelIsOkToJoin( Channel& channel )
{
    std::string channelName = channel.getChannelName();

    if (channels[channelName] != NULL)
        return (true);

    return (false);
}

void    Server::sendPrivMessages( std::string buffer, int userFd, int targetFd )
{
    if (targetFd == _serverFd || targetFd == userFd)
        return;

    send(targetFd, buffer.c_str(), buffer.size(), 0);
}

void    Server::sendMessageToAllChannelMembers( std::string buffer, int fd )
{
    if (fd == _serverFd)
        return;

    std::vector<std::string> splittedBuffer;
    std::vector<std::string> splittedBufferWhiteSpace;

    splittedBuffer.push_back(buffer);
    splitStringSep(splittedBuffer, "\r\n");
    splittedBufferWhiteSpace = splitString(splittedBuffer[0]);
    
    if (isACommand(splittedBufferWhiteSpace[0], *this))
        return;

    std::map< int, User* >::iterator    it = _userMap.find(fd);
    std::string                         channelName;

    if (it == _userMap.end())
        return;

    channelName = it->second->getChannelName();

    if (channels[channelName] == NULL)
        return ;

    channels[channelName]->sendMessageToEveryone(buffer, fd);
}

void    Server::deleteChannel( Channel* channel )
{
    std::vector<std::string>::iterator  it = _channelNames.begin();
    std::string                         channelName = channel->getChannelName();

    // je supprime le nom de channel de mon vector _channelNames
    while (it != _channelNames.end())
    {
        if (*it == channelName)
            it = _channelNames.erase(it); // récupère l'itérateur de l'élément suivant
        else
            ++it;
    }

    std::map<std::string, Channel*>::iterator itMap = channels.find(channelName);

    if (itMap != channels.end())
    {
        delete itMap->second; // Libère la mémoire allouée pour l'objet Channel
        channels.erase(itMap);
    }
}

/*************************************************************************************/
/*                            USER FUNCTIONS                                         */
/*************************************************************************************/

void    Server::removeUserWithFd( int fd ) 
{
    delete _userMap[fd];
    _userMap.erase(_userMap.find(fd));

    _nbUsers--;
}

void    Server::removeUser( int i ) 
{
    delete _userMap[_fds[i].fd];
    _userMap.erase(_userMap.find(_fds[i].fd));
    _fds[i] = _fds[_nbUsers -  1];

    _nbUsers--;
}

void    Server::addUser( int fd) 
{  
    if (fd < 0)
        return;
    if ( _nbUsers < _maxUsers && _userMap[fd] == NULL)
    {
        User  *newUser = new User(fd, this);
        _userMap[fd] = newUser;
        _nbUsers++;
    }
}

/*************************************************************************************/
/*                           SERVER FUNCTIONS                                        */
/*************************************************************************************/

void    Server::cDuPropre( void )
{
    std::map< int, User* > :: iterator              itUser;
    std::map< std::string, Channel* > :: iterator   itChannel;

    if (!_userMap.empty())
    {
        for (itUser = _userMap.begin(); itUser != _userMap.end(); itUser++)
        {
            close(itUser->first);
            delete itUser->second;
        }
    }

    if (!channels.empty())
    {
        for (itChannel = channels.begin(); itChannel != channels.end(); itChannel++)
            delete itChannel->second;
    }

    close(_epollFd);
    close(_serverFd);
}    

void    Server::sigintHandler(int sig)
{
        (void)sig;
        interrupt = true;
 
        std::cout << RED << "[SIGINT HANDLER]" <<  CRESET << "- SIGINT reçu, arrêt du programme" << std::endl;
}

int     Server::createSocket( void )
{
    int enable = 1;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
        sendError("[CREATE SOCKET] - Failed to create socket");
   
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    
    fcntl(serverSocket, F_SETFL, O_NONBLOCK);
    signal(SIGINT, &Server::sigintHandler);
    return ( serverSocket );
}

sockaddr_in Server::bindSocket( int serverSocket ) 
{
    sockaddr_in serverAddress;
    int         bindResult;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    bindResult = bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    
    if (bindResult < 0) 
    {
        sendError("[BIND SOCKET] - Failed to bind socket to port");
        throw std::exception();
    }

    return ( serverAddress );
} 

int    Server::acceptconnexion(int server_fd)
{
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int client_fd;

    client_fd = accept(server_fd, (sockaddr*)&clientAddress, &clientAddressSize);
    if (client_fd < 0)
        sendError("[ACCEPT CONNECTION] - Failed to accept incoming connection");
    else
    {
        std::cout << YEL << "\n[ACCEPT CONNECTION]" << CRESET << " - Accepted connection: fd #" << client_fd << std::endl;
        addUser(client_fd);
    }
    return(client_fd);
}

static void    add_fd_to_poll(int epoll_fd, int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP ;
    event.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event)) //on ajoute le fd du server a la liste de poll;
    {
		std::cout<< "[ADD FD TO POLL] - Failed to add file descriptor to epoll" << std::endl;
		close(epoll_fd);
        throw std::exception();
	}
}

static int   init_epoll()
{
    int epoll_fd = epoll_create1(0); // on init le epoll_fd.

	if (epoll_fd == -1) 
    {
		std::cerr << "[INIT EPOLL] - Failed to create epoll file descriptor\n" << std::endl;
		return 1;
	}
    return (epoll_fd);
}

int    Server::runServer( void ) 
{
    char                        buffer[1024];
    int                         nBytes;
    int                         event_count;
    int                         client_fd;
    std::string                 data = "";
    std::vector<std::string>    splittedBuffer;

    _serverFd = createSocket();
    sockaddr_in serverAddress = bindSocket( _serverFd ); //on init le server.
    // Listen for incoming connections
    int listenResult = listen(_serverFd, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("[RUN SERVER] - Failed to listen for incoming connections");
        return 1;
    }
    // on init le epoll_fd. 
    _epollFd = init_epoll(); 
    add_fd_to_poll(_epollFd, _serverFd); //on ajoute le fd du server a la liste de poll;
    struct epoll_event events[100];   
	while (interrupt != true) 
    {
		event_count = epoll_wait(_epollFd, events, 1, -1);
		// std::cout << "[RUN SERVER] - " << event_count << " ready events" << std::endl;
		for (int i = 0; i < event_count; i++)
        {
			// std::cout<< "[RUN SERVER] - Reading file descriptor " << events[i].data.fd << std::endl;
            if (events[i].events & EPOLLRDHUP)
            {
                if (events[i].data.fd == _serverFd)
                {
                    interrupt = true;
                    break;
                }
                else
                    quit("", *_userMap[events[i].data.fd]);
                continue;
            }
            if (events[i].data.fd == _serverFd)
            {
                client_fd = acceptconnexion(_serverFd);
                add_fd_to_poll(_epollFd, client_fd); //on ajoute le fd du nouvequ client a la liste de poll;
            }
            std::memset(buffer, 0, sizeof(buffer));
			nBytes = recv(events[i].data.fd, buffer, 1023, MSG_DONTWAIT);
            if (nBytes < 0)
                continue;
            if (nBytes == 0)
            {
                removeUser(events[i].data.fd);
                std::memset(buffer, 0, sizeof(buffer));
                data.clear();
                continue;
            }
            if (nBytes > 0)
            {
                data += buffer; // j'append les buffer a data (poentiellement des reliquas non recus au tour d'avant)
                if (data.find("\r\n") == std::string::npos) // si je trouve pas de \r\n dans le buffer, je quitte la condition pour pouvoir l'append au tour d'apres
                    break;
                if (data == "\r\n")
                {
                    data.clear();
                    break;
                }
                splittedBuffer.push_back(data);
                data.clear();
                splitStringSep(splittedBuffer, "\r\n");
                for (size_t j = 0; j < splittedBuffer.size(); j++)
                    _userMap[events[i].data.fd]->handleCommand(splittedBuffer.at(j));
                splittedBuffer.clear();
            }
		}
	}
    cDuPropre();
    return (0);
}
