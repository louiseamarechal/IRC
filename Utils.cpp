#include "Utils.hpp"
#include <unistd.h>
#include <signal.h>

void   sendError( std::string message ) {
    std::cerr << message << std::endl;
}

void sigintHandler(int sig) {
        (void)sig;
        // Affiche un message et termine proprement le processus
        std::cout << "SIGINT reçu, arrêt du programme" << std::endl;
        exit(0);
}

std::string removeConsecutiveWhitespace( std::string buffer ) {

    char                    whitespace = 32;
    std::string             result;
    std::string::iterator   it = buffer.begin();
    
    while ( *it == whitespace )
        buffer.erase(it);

    for (it = buffer.begin(); it != buffer.end(); ++it)
    {
        if (*it == whitespace && (it + 1) != buffer.end() && *(it + 1) == whitespace)
            continue;

        result += *it; 
    }

    if (!result.empty() && result.back() == whitespace)
        result.pop_back();

    return result;
}