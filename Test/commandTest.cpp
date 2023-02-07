#include "../Reply.hpp"
#include <iostream>
#include <stdio.h>

int main(void) 
{
    Server  server;
    User    user(4, server);

    user.setUserNick("lmarecha");

    std::cout << "1 = " << sendMessage1(1, user, server, user.getUserNick()).c_str() << std::endl;
    std::cout << "2 = " << sendMessage2(2, user, server, server.getServerName(), server.getVersion()).c_str() << std::endl;
    std::cout << "3 = " << sendMessage1(3, user, server, "Jan 24th 2023").c_str() << std::endl;
    std::cout << "4 = " << sendMessage4(4, user, server, server.getServerName(), server.getVersion(), "oOxif", "oOxif").c_str() << std::endl;

    return (0);
}