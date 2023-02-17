#include "Server.hpp"
#include <algorithm>
#include <unistd.h>
#include "user/User.hpp"
#include "../includes/utils.hpp"
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <iostream>       // std::cout
#include <string> 

Server*                 global_serv;
std::vector<int>         g_fdList;

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

Server::Server( void ) : _port(0),
                        _version("2.0"),
                        _serverName("JLA.irc.com"),
                        _password(""),
                        _creationDate("Wed Feb 8 15:53:25 2023"),
                        _maxUsers(10),
                        _serverFd(0)
                        // _nbUsers(0),

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
    
    // _commandMap['PASS'] = &checkPass;
    // _commandMap['PRIVMSG'] = &sendPrivMsg;
    // return ;
}

Server::~Server( void ) 
{ 
    std::cout<<"destructor server called"<<std::endl;
    // for (size_t i = 0; i < g_fdList.size(); i++)
    // {
    //     delete _userMap[g_fdList[i]];
    //     close(g_fdList[i]);
    // }   
    // for (int i = 0; i < _nbUsers; i++)
    //     delete _userMap[i];
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

// Channel*                    Server::getChannel( std::string channelName ) const { return (_channels[channelName]); }

// std::map<std::string, Channel*> Server::getChannels( void ) const { return (_channels); };

std::map<std::string, void (*)(std::string params, User &user)>    Server::getCommandMap(void) const { return (_commandMap);}

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
    else 
    {
        std::cout<<" remove old nickname failed" << std::endl;
    }
}

/*************************************************************************************/
/*                             CHANNEL FUNCTIONS                                     */
/*************************************************************************************/

void    Server::setChannels( Channel* channel )
{
    std::string channelName = channel->getChannelName();

    _channelNames.push_back(channelName);
    if (channels[channelName] == NULL)
    {
        channels[channelName] = channel;
        std::cout << channels[channelName]->getChannelName() << " is now in the server public channels map ! His channelOperator is : " <<  channels[channelName]->getChannelOperator() << std::endl;
    }
}

bool    Server::channelIsOkToJoin( Channel& channel )
{
    std::string channelName = channel.getChannelName();

    if (!(channel.getChannelMembers().empty()))
    {
        std::cout << "Channels already has members" << std::endl;
        
    }
    if (channels[channelName] != NULL)
        return (true);

    return (false);
}

void    Server::sendMessageToAllChannelMembers( std::string buffer, int fd )
{
    if (fd == _serverFd)
        return;

    std::vector<std::string> splittedBuffer;
    std::vector<std::string> splittedBufferWhiteSpace;

    splittedBuffer.at(0) = buffer;
    splitStringSep(splittedBuffer, "\r\n");

    splittedBufferWhiteSpace = splitString(splittedBuffer[0]);

    if (isACommand(splittedBuffer[0]))
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
        {
            std::cout << "I'm about to remove this channel name from _channelNames : " << *it << std::endl;
            it = _channelNames.erase(it); // récupère l'itérateur de l'élément suivant
            std::cout << "Name has been removed from the _channelNames vector." << std::endl;
        }
        else
        {
            ++it;
        }
    }

    // je cherche le bon channel et je le supprime
    std::map<std::string, Channel*>::iterator itMap = channels.find(channelName);

    if (itMap != channels.end())
    {
        std::cout << "Removing channel " << channelName << " from the server public channels map !" << std::endl;
        delete itMap->second; // Libère la mémoire allouée pour l'objet Channel
        channels.erase(itMap);
    }
    // itMap est un itérateur qui pointe versla clé channelName dans la map. 
    // itMap->second, permet d'acceder à la valeur associée à la clé -> un pointeur vers l'objet Channel.
}

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

void    Server::removeUser( int i ) 
{ 
    //ICI FAIRE BLOC TRY AND CATCH pourjeter une exception si on trouve pas le fd dans la mapde user utiliser Map.at() pour etre sure qu ca existe et que ca cree pas un truc random u'on supprime apres.
        delete _userMap[_fds[i].fd];
    _fds[i] = _fds[_nbUsers -  1];

    _nbUsers--;
}

// PROPOSITON DE LEA :
// void Server::removeUser(int clientFd) {
//     // Trouver l'identifiant du client dans la table de hachage
//     auto userIter = _userMap.find(clientFd);
//     if (userIter == _userMap.end())
//         return;

//     // Supprimer l'entrée associée à ce client dans la table de hachage
//     _userMap.erase(userIter);

//     // Réduire le compteur de clients connectés
//     _nbUsers--;

//     // Fermer la socket associée au client déconnecté
//     close(clientFd);

//     // Mettre à jour la liste des descripteurs de fichiers pollfd
//     for (int i = 0; i < _nbUsers; i++) {
//         if (_fds[i].fd == clientFd) {
//             for (int j = i; j < _nbUsers - 1; j++)
//                 _fds[j] = _fds[j + 1];
//             break;
//         }
//     }
// }

void    Server::addUser( int fd) 
{  
    g_fdList.push_back(fd);
    if ( _nbUsers < _maxUsers && _userMap[fd] == NULL)
    {
        User  *newUser = new User(fd, this);
        _userMap[fd] = newUser;
        _nbUsers++;
    }
    else
        std::cout << "Too many users ! " << std::endl;
}

// void    Server::disconnect_all(void)
// {
//     delete this;
//     return;
// }
void Server::sigintHandler(int sig)
{
        (void)sig;
         for (size_t i = 0; i < g_fdList.size(); i++)
        {
            std::map< int, User* > :: iterator it = global_serv->_userMap.find(g_fdList[i]);
            if (it != global_serv->_userMap.end())
            {   
                delete it->second;
                global_serv->_userMap.erase(it);
                close(g_fdList[i]);
            }
        }
        close (3);
        g_fdList.clear();
        delete global_serv;
        std::cout << "SIGINT reçu, arrêt du programme" << std::endl;
        exit(0);
       
}

int     Server::createSocket( void )
{
    int enable = 1;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
        sendError("Failed to create socket");
    else
        std::cout << "Socket created !" << std::endl;
   
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    
    fcntl(serverSocket, F_GETFL, O_NONBLOCK);
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
        sendError("Failed to bind socket to port");
        throw std::exception();
    }
    else
        std::cout << "Success, socket binded !" << std::endl;

    return ( serverAddress );
} 

int    Server::acceptconnexion(int server_fd)
{
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int client_fd;

    client_fd = accept(server_fd, (sockaddr*)&clientAddress, &clientAddressSize);
    if (client_fd < 0)
        sendError("Failed to accept incoming connection");
    else
    {
        std::cout<< "Accepted connection: fd #" << client_fd <<std::endl;
        addUser(client_fd);
    }
    return(client_fd);
}

static void    add_fd_to_poll(int epoll_fd, int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event)) //on ajoute le fd du server a la liste de poll;
    {
		std::cout<<"Failed to add file descriptor to epoll"<<std::endl;
		close(epoll_fd);
        throw std::exception();
	}
}

static int   init_epoll()
{
    int epoll_fd = epoll_create1(0); // on init le epoll_fd.

    std::cout<<"epoll_fd = "<<epoll_fd<<std::endl;
	if (epoll_fd == -1) 
    {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
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
    std::string                 data;
    std::vector<std::string>    splittedBuffer;

    _serverFd = createSocket();
    sockaddr_in serverAddress = bindSocket( _serverFd ); //on init le server.
    // Listen for incoming connections
    int listenResult = listen(_serverFd, serverAddress.sin_port);
    if (listenResult < 0) {
        sendError("Failed to listen for incoming connections");
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;
    // on init le epoll_fd. 
    int epoll_fd = init_epoll(); 
    add_fd_to_poll(epoll_fd, _serverFd); //on ajoute le fd du server a la liste de poll;
    struct epoll_event events[100];   
	while (1) 
    {
		std::cout << "\nPolling for input..."<<std::endl;
		event_count = epoll_wait(epoll_fd, events, 1, -1);
		std::cout << event_count << " ready events" << std::endl;
		for (int i = 0; i < event_count; i++)
         {
			std::cout<< "Reading file descriptor " << events[i].data.fd << std::endl;
			std::cout<< "server fd = " << _serverFd << std::endl;
            if (events[i].data.fd == _serverFd)
            {
                client_fd = acceptconnexion(_serverFd);
                add_fd_to_poll(epoll_fd, client_fd); //on ajoute le fd du nouvequ client a la liste de poll;
            }
            std::memset(buffer, 0, sizeof(buffer));
			nBytes = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
            std::cout << "Buffer Server = " << buffer << std::endl;
            std::cout << "nBytes  = " << nBytes << std::endl;
            if (nBytes <= 0)
            {
                removeUser(events[i].data.fd);
                continue;
            }
            if (nBytes > 0)
            {
                // buffer[nBytes] = '\0';
                data.append(buffer, nBytes); // j'append les buffer a data (poentiellement des reliquas non recus au tour d'avant)
                if (data.find("\r\n") == std::string::npos) // si je trouve pas de \r\n dans le buffer, je quitte la condition pour pouvoir l'append au tour d'apres
                    break;
                if (data == "\r\n")
                {
                    data.clear();
                    break;
                }
                std::cout << "Data Server (after append()) = " << data << std::endl;
                
                sendMessageToAllChannelMembers(data, events[i].data.fd);
                splittedBuffer.push_back(data);
                data.clear();
                splitStringSep(splittedBuffer, "\r\n");
                for (size_t j = 0; j < splittedBuffer.size(); j++)
                {
                      std::cout << "Command send to Handle Commande -- Server : " << splittedBuffer.at(j) << std::endl;
                    _userMap[events[i].data.fd]->handleCommand(splittedBuffer.at(j));
                }
                splittedBuffer.clear();
            }
		}
	}
    return (0);
}



	