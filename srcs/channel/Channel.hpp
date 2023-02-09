# ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel {

    public :


    private :
        // std::string                     _channelShortName;
        std::string                     _channelName;
        std::map<std::string, User *>   _channelMembers; // est ce que Map est le plus approprie ? -> acceder a un User via son nickname
        std::string                     _channelServerName;
        User*                           _channelOperator;
        User*                           _channelCreator;

};

#endif