#include <string>
#include <map>
#include <iostream>

std::map< std::string, std::string >  commandParser( std::string buffer ) {
    
    std::map< std::string, std::string >    commandMap;
    std::string                             whitespace = " ";
    int                                     position;

    position = buffer.find(whitespace); // retourne premier espace trouve
    std::cout << "whitespace is at position: " << position << std::     endl;

    commandMap["command"] = buffer.substr(0, position); // copie la commande
    commandMap["parameters"] = buffer.substr(position + 1); // copie tout le reste de la string
    
    std::cout << "Command = " <<  commandMap["command"] << std::endl;
    std::cout << "Parameters = " <<  commandMap["parameters"] << std::endl;

    return(commandMap);
}

int main( void ) {

    std::string buffer = "USER lmarecha 127.0.0.1 : Louise";

    commandParser(buffer);

    return (0);
}