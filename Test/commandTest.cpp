#include "../Command.hpp"
#include <iostream>

int main(void) 
{
    User    user;
    Server  server;

    user.setUserNick("lmarecha");
    std::cout << formatMessage(1, user, server, user.getUserNick(), "", "", "") << std::endl;
    std::cout << formatMessage(2, user, server, server.getServerName(), server.getVersion(), "", "") << std::endl;
    std::cout << formatMessage(3, user, server, "Jan 24th 2023", "", "", "") << std::endl;
    std::cout << formatMessage(4, user, server, server.getServerName(), server.getVersion(), "oOxif", "oOxif") << std::endl;

    return (0);
}