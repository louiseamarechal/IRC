/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:53:03 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:53:05 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include "user/User.hpp"
#include "utils.hpp"
#include <cstdlib>

bool interrupt = false;

int main( int argc, char **argv ) 
{
    if ( argc != 3 ) {

        std::cout << "Please follow requested format : ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    if (std::string(argv[2]) != "password")
    {
        std::cout << "Wrong Password, please try again !" << std::endl;
        return (1);
    }

    Server  *serverJLA = new Server();

    serverJLA->setPort(atoi(argv[1]));
    serverJLA->setPassword(argv[2]);
    serverJLA->runServer();

    delete serverJLA;
    return (0);
}

