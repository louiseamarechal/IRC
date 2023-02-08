#include "user/User.hpp"
#include "server/Server.hpp"
#include <string.h>

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

bool        User::getIsUserRegistered() const { return (_isUserRegistered); }

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

void    User::setIsNickSet(bool value) {
    
    _isNickSet = value;

    if (_isNickSet == true && _isUserSet == true)
        setIsUserRegistered(true);
}

void    User::setIsUserSet( bool value ) { 
    
    _isUserSet = value;
    
    if (_isNickSet == true && _isUserSet == true)
        setIsUserRegistered(true);    
}

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

// void User::handleCommand(std::string buffer)
// {
//     std::string     whitespace = " ";
//     std::string     s1;
//     std::string     s2;
//     int             position;

//     std::cout << "Handle Command -- Buffer = " << buffer << std::endl;

//     position = buffer.find(whitespace); // retourne premier espace trouve
//     s1 = buffer.substr(0, position); // copie la commande
//     position++;
//     if (position == *s1.end())
//         s2 = "";
//     else
//         s2 = buffer.substr(position, buffer.size()-s1.size()-3); // copie tout le reste de la string
//     std::cout << "Handle Command -- Command = " << s1 << std::endl;
//     std::cout << "Handle Command -- Params = " << s2 << "fini params";
//     if (getServer()->getCommandMap().count(s1) > 0)
//         getServer()->getCommandMap()[s1](s2, *this);
// }

void User::handleCommand(std::string buffer)
{
    std::string         whitespace = " ";
    std::string         s1;
    std::string         s2;
    std::string         tmp;
    size_t              pos = 0;
    size_t              endlinepos;

    std::cout << "Handle Command -- Buffer = " << buffer << std::endl;
   

    while(buffer.size() != 0)
    { 
        std::cout << "Buffer size = " << buffer.size() << std::endl;
    std::cout << "pos  = " << pos << std::endl;
        pos = buffer.find(whitespace);// retourne premier espace trouve
        endlinepos = buffer.find("\n");// retourne premier \n trouve
        s1 = buffer.substr(0, pos); // copie la commande
        pos++;
        s2 = buffer.substr(pos, endlinepos - pos - 1);
        if (endlinepos != buffer.size())
        {  
            tmp = buffer.substr(endlinepos + 1, buffer.size());
            buffer = tmp;
        }
        pos = s2.size();
        std::cout << "Handle Command -- Command = " << s1 << std::endl;
        std::cout << "Handle Command -- Params = " << s2 <<std::endl;
        if (getServer()->getCommandMap().count(s1) > 0)
            getServer()->getCommandMap()[s1](s2, *this);
    }
}