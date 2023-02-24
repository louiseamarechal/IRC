# ifndef UTILS_HPP
# define UTILS_HPP

#include "server/Server.hpp"
#include "user/User.hpp"
#include "commands.hpp"
#include "channel/Channel.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <iostream>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void                        sendError( std::string message );
// void                        sigintHandler( int sig );
std::string                 removeConsecutiveWhitespace( std::string buffer ); // supprime les whitespaces qui se suivent + tous ceux au debut du mot et touc ceux a la fin a la fin : "     Hello  World !  " -> "Hello World !"
std::vector<std::string>    splitString( std::string params ); // split la string a chaque wihtespace
std::string                 toUpper( std::string str );
// std::vector<std::string>    splitStringSep( std::string params , std::string sep );
bool                        isACommand(std::string buffer, Server& server);
void                        splitStringSep( std::vector<std::string>    &params, std::string sep );
bool                        isInVectorList( std::string target, std::vector<std::string> stringVector );

template <class T, class U>
void                        displayMap(const std::map<T, U>& map, const std::string& name);

#endif