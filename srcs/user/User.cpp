#include "user/User.hpp"
#include "server/Server.hpp"
#include <string.h>

/*************************************************************************************/
/*                              CONSTRUCTORS                                         */
/*************************************************************************************/

User::User(int fd, Server *server) : _userLoggin(""),
                                    _userFullName(""),
                                    _userNick(""),
                                    _userFd(fd),
                                    _isNickSet(false),
                                    _isUserSet(false),
                                    _isUserRegistered(false),
                                    _isOper(false),
                                    _server(server),
                                    _userChannel()
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
        _isOper = rhs.getIsOper();
        _server = rhs.getServer();
    }

	return (*this);
}


User::~User( void )
{ 
    std::cout<<"destructor user called for ==" << getUserFd() <<std::endl;
    // delete this;
    return ; 
} // supprimer les users ?

/*************************************************************************************/
/*                              GETTERS                                              */
/*************************************************************************************/

int         User::getUserFd( void ) const { return (_userFd); }

bool        User::getIsUserRegistered() const { return (_isUserRegistered); }

bool        User::getIsNickSet() const{return(_isNickSet);}

bool        User::getIsUserSet() const{return(_isUserSet);}

bool        User::getIsOper() const {return(_isOper);}

Server*     User::getServer() const{return(_server);}

Channel&    User::getUserChannel( void ) const { return (*_userChannel); }

std::string User::getUserNick( void ) const { return (_userNick); }

std::string User::getUserLoggin( void ) const { return ( _userLoggin ); }

std::string User::getUserFullName( void ) const { return( _userFullName ); }

std::string User::getChannelName( void ) const { return( _channelName ); }

/*************************************************************************************/
/*                              SETTERS                                              */
/*************************************************************************************/

void    User::setUserNick( std::string nick ) { _userNick = nick; }

void    User::setUserLoggin( std::string loggin ) { _userLoggin = loggin; }

void    User::setUserFullName( std::string fullName ) { _userFullName = fullName; }

void    User::setIsUserRegistered(bool value) {_isUserRegistered = value;}

void    User::setOper(bool value) {_isOper = value;}

void    User::setIsNickSet(bool value) {
    
    _isNickSet = value;

    if (value == true)
        std::cout << "NICK is now set" << std::endl;

    if (_isNickSet == true && _isUserSet == true)
    {
        setIsUserRegistered(true);
        std::cout << "User has been set to status : REGISTERED " << std::endl;
    }
}

void    User::setIsUserSet( bool value ) { 
    
    _isUserSet = value;
    
    if (value == true)
        std::cout << "USER is now set" << std::endl;

    if (_isNickSet == true && _isUserSet == true)
    {
        setIsUserRegistered(true);    
        std::cout << "User status has been set to : REGISTERED " << std::endl;
    }
}

void    User::setUserChannel( Channel* channel )
{
    _userChannel = channel; 
    _channelName = channel->getChannelName();
}

// void    User::addUserToChannel( std::string channelName) { _server->addMemberToChannel(*this, channelName); }

/*************************************************************************************/
/*                              FUNCTIONS                                            */
/*************************************************************************************/

void User::handleCommand(std::string buffer)
{
    std::string                 whitespace = " ";
    std::string                 command;
    std::string                 params;
    size_t                      position;

    position = buffer.find(whitespace);

    if (position == std::string::npos)
    {
        command = toUpper(buffer.substr(0, buffer.size()));
        params = "";
    }
    else
    {
        command = toUpper(buffer.substr(0, position));
        position++;
        params = buffer.substr(position, buffer.size() - position);
    }
    
    std::cout << "Handle Command -- Command = " << command << std::endl;
    std::cout << "Handle Command -- Params = " << params <<std::endl;
    std::cout << "savoir si la commande correspond  a un vrai truc == " << getServer()->getCommandMap().count(command) << std::endl;
    if (getServer()->getCommandMap().count(command) > 0)
        getServer()->getCommandMap()[command](params, *this);
}

void    User::clearChannel( void )
{
    _channelName.clear(); 
    _userChannel = NULL;

    std::cout << "---------- PART ----------" << std::endl;
    std::cout << "User ----- _channelName = " << _channelName << std::endl;
    std::cout << "User ----- _userChannel = " << _userChannel << std::endl;
}