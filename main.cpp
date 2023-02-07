/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouyer <jbouyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:48:29 by jbouyer           #+#    #+#             */
/*   Updated: 2023/02/01 15:48:36 by jbouyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include <cstdlib>

int main( int argc, char **argv ) 
{
    if ( argc != 3 ) {

        std::cout << "Please follow requested format : ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    Server  *serverJLA = new Server();

    serverJLA->setPort(atoi(argv[1]));
    serverJLA->setPassword(argv[2]);
    serverJLA->runServer();

    return (0);
}

