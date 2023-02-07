#include "User.hpp"
#include "Server.hpp"

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

User::User(int fd, Server *server) : _userLoggin(""), _userFullName(""), _userNick(""), _userFd(fd), _isNickSet(false), _isUserSet(false),  _isUserRegistered(false), _server(server)
{ 
    
    std::cout << "New User created : fd = " << _userFd << std::endl;
    std::cout << "Server Name from User constructor : " << this->getServer()->getServerName() << std::endl;
    return ;
}


User&   User::operator=( User const & rhs ) 
{

	if (this != &rhs)
    {
        _userFd = rhs.getUserFd();
        _userFullName = rhs.getUserFullName();
        _userNick = rhs.getUserNick();
        _userLoggin = rhs.getUserLoggin();
        _isNickSet = rhs.getIsNickSet();
        _isUserSet = rhs.getIsUserSet();
        _isUserRegistered = rhs.getIsUserRegistered();
        _server = rhs.getServer();
    }

	return (*this);
}


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

Server*     User::getServer() const{return(_server);}

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

void    User::setUserNick( std::string nick ) { _userNick = nick; }

void    User::setUserLoggin( std::string loggin ) { _userLoggin = loggin; }

void    User::setUserFullName( std::string fullName ) { _userFullName = fullName; }

void    User::setIsUserRegistered(bool value) {_isUserRegistered = value;}

void    User::setIsNickSet(bool value) {_isNickSet = value;}

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

void User::handleCommand(std::string buffer)
{
    std::string     whitespace = " ";
    std::string     s1;
    std::string     s2;
    int             position;

    std::cout << "Handle Command -- Buffer = " << buffer << std::endl;

    position = buffer.find(whitespace); // retourne premier espace trouve
    s1 = buffer.substr(0, position); // copie la commande
    position++;
    if (position == *s1.end())
        s2 = "";
    else
        s2 = buffer.substr(position, buffer.size()-s1.size()-3); // copie tout le reste de la string
    std::cout << "Handle Command -- Command = " << s1 << std::endl;
    std::cout << "Handle Command -- Params = " << s2 ;
    if (getServer()->getCommandMap().count(s1) > 0)
        getServer()->getCommandMap()[s1](s2, *this);
}