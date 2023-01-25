#include "User.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

User::User( void ) { return ; }

User::User ( int fd ) : _userFd( fd ) { return ; }

User::~User( void ) { return ; } // supprimer les users ?

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

int User::getUserFd( void ) const { return (_userFd); }

std::string User::getUserNick( void ) const { return (_userNick); }

std::string User::getUserLoggin( void ) const { return ( _userLoggin ); }

std::string User::getUserFullName( void ) const { return( _userFullName ); }

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

// void    User::setUserFd( int fd ) { _userFd = fd; }

void    User::setUserNick( std::string nick ) { _userNick = nick; }

void    User::setUserLoggin( std::string loggin ) { _userLoggin = loggin; }

void    User::setUserFullName( std::string fullName ) { _userFullName = fullName; }

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

std::map< std::string, std::string > User::commandParser( std::string buffer ) {
    
    std::map< std::string, std::string >    commandMap;
    std::string                             whitespace = " ";
    int                                     position;

    position = buffer.find(whitespace); // retourne premier espace trouve

    commandMap["command"] = buffer.substr(0, position); // copie la commande
    commandMap["parameters"] = buffer.substr(position + 1); // copie tout le reste de la string
    
    return(commandMap);
}
