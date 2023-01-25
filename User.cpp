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