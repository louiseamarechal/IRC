#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"

int main( int argc, char **argv ) {

    if ( argc != 3 ) {

        std::cout << "Please follow requested format : ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    Server  serverJLA;

    serverJLA.setPort(atoi(argv[1]));
    serverJLA.setPassword(argv[2]);
    serverJLA.runServer();

    return (0);
}