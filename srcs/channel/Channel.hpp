/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:48:55 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 14:01:43 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "user/User.hpp"
#include "server/Server.hpp"
#include "reply.hpp"
#include <vector>

class Server;
class User;

class Channel {

    public :
        Channel( std::string name, Server& server, User& channelCreator );
        ~Channel( void );

        Channel&    operator=( Channel const & rhs );

        std::string                     getChannelName( void ) const;
        std::vector<User*>              getChannelMembers( void ) const;
        Server&                         getChannelServer( void ) const;
        User*                           getChannelOperator( void ) const;
        User*                           getChannelCreator( void ) const;
        std::string                     getAllMembersName( void ) const;

        void                            addChannelMembers( User& user );
        void                            removeChannelMembers( User& user );
        void                            sendMessageToEveryone( std::string buffer, int fd );

    private :
        std::string                      _channelName;
        std::vector<User*>               _channelMembers;
        Server&                          _server;
        User*                            _channelOperator;
        User*                            _channelCreator;

};

bool    channelNameFormatIsOk( std::string name );

#endif