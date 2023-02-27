#include "commands.hpp"

void    kick( std::string params, User &user )
{
    std::vector< std::string >  splittedParams;
    std::vector< std::string >  channels;
    std::vector< std::string >  users;

    splittedParams = splitString(params);
    // check if params.empty() -> ERR_NEEDMOREPARAMS
    // divide the params with whitespaces as sep to get all the 
    // check that there is at least 1 channel and the list of users to kick
        // otherwise check that there is 1 channel per user 
    // check that the channel exists -> ERR_NOSUCHCHANNEL
    // check that the user using the cmd is OPER -> ERR_CHANOPRIVSNEEDED
    // chack that the user he wants to kick is in a channel -> ERR_USERNOTINCHANNEL
    // check that user asking to KICK is on channel -> ERR_NOTONCHANNEL
}

// ERR_NEEDMOREPARAMS
// ERR_BADCHANMASK
// ERR_USERNOTINCHANNEL
// ERR_NOSUCHCHANNEL
// ERR_CHANOPRIVSNEEDED
// ERR_NOTONCHANNEL