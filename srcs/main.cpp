#include "server/Server.hpp"
#include "user/User.hpp"
#include "utils.hpp"
#include <cstdlib>

int main( int argc, char **argv ) 
{
    if ( argc != 3 ) {

        std::cout << "Please follow requested format : ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    Server  *serverJLA = new Server();

    global_serv = serverJLA;
    serverJLA->setPort(atoi(argv[1]));
    serverJLA->setPassword(argv[2]);
    serverJLA->runServer();

    delete serverJLA;
    return (0);
}

