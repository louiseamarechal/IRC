#include "User.hpp"
#include "Server.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

User::User(int fd, Server &server) : _isNickSet(false), _isUserSet(false), _isUserRegistered(false), _server(server), _userFd( fd ) { 
    
    std::cout << "New User created : fd = " << _userFd << std::endl;
    return ;
}

// User::User ( int fd, Server* server) : _userFd( fd ), _server(server) { return ; }

User::~User( void ) { return ; } // supprimer les users ?

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

int         User::getUserFd( void ) const { return (_userFd); }

std::string User::getUserNick( void ) const { return (_userNick); }

std::string User::getUserLoggin( void ) const { return ( _userLoggin ); }

std::string User::getUserFullName( void ) const { return( _userFullName ); }

bool        User::getIsUserRegistered() const {return (_isUserRegistered);}

bool        User::getIsNickSet() const{return(_isNickSet);}

bool        User::getIsUserSet() const{return(_isUserSet);}

Server&     User::getServer() const{return(_server);}




/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

// void    User::setUserFd( int fd ) { _userFd = fd; }

void    User::setUserNick( std::string nick ) { _userNick = nick; }

void    User::setUserLoggin( std::string loggin ) { _userLoggin = loggin; }

void    User::setUserFullName( std::string fullName ) { _userFullName = fullName; }

void    User::setIsUserRegistered(bool value) {_isUserRegistered = value;}

void    User::setIsNickSet(bool value) {_isNickSet = value;}

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

// std::map< std::string, std::string > User::commandParser( std::string buffer ) {
    
//     std::map< std::string, std::string >    commandMap;
//     std::string                             whitespace = " ";
//     int                                     position;

//     position = buffer.find(whitespace); // retourne premier espace trouve

//     commandMap["command"] = buffer.substr(0, position); // copie la commande
//     commandMap["parameters"] = buffer.substr(position + 1); // copie tout le reste de la string
    
//     return(commandMap);
// }


void User::handleCommand(std::string buffer)
{
    std::string     whitespace = " ";
    std::string     s1;
    std::string     s2;
    int             position;

    position = buffer.find(whitespace); // retourne premier espace trouve
    s1 = buffer.substr(0, position); // copie la commande
    s2 = buffer.substr(position + 1); // copie tout le reste de la string

//     if (_server.commandMap[s1] != NULL)
//         _server.commandMap[s1](s2, this);
}