#include <command.hpp>

// only used if User is in a channel

    // USER
    // delete/remove _userChannel
    // clear _channelName

    // CHANEL
    // remove User de _channelMembers
    // clear _channelOperator ->  remplace par qui ?
    // clear _channelCreator -> remplace par qui ?

// if  User is the last Member of the Channel

    // SERVER :
    // delete server.channels
    // remove de _channelNames

// void    partChannel(std::string str, User &user)
// {

// }