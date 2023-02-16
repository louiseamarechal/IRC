#include "utils.hpp"
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
    
    if (buffer.empty())
        return (NULL);

    while ( *it == whitespace )
        buffer.erase(it);

    for (it = buffer.begin(); it != buffer.end(); ++it)
    {
        if (*it == whitespace && (it + 1) != buffer.end() && *(it + 1) == whitespace)
            continue;

        result += *it; 
    }

    if (!result.empty() && result[result.size() - 1] == whitespace)
        result.erase(result.size() - 1);

    return result;
}

std::vector<std::string> splitStringSep( std::string params , std::string sep )
{
    std::vector<std::string>        splittedParams;
    size_t                          startPos = 0;
    size_t                          endPos = 0;
    int                             sepLength = sep.length();
    std::string                     result;

    if (params.empty())
        return (splittedParams);

    while ((endPos = params.find(sep, startPos)) != std::string::npos)
    {
        result = params.substr(startPos, endPos - startPos); // on substr juste avant \r\n
        std::cout << "Splitted String Sep result = " << result << std::endl;
        startPos = endPos + sepLength; // on avance startPos apres \r\n
        splittedParams.push_back(result); // on ajoute notre str au vector
    }

    return (splittedParams);
}

std::vector<std::string> splitString( std::string params ) {

    std::vector<std::string>        splittedParams;
    char                            whitespace = 32;
    std::string::iterator           it = params.begin();
    std::string                     result;

    if (params.empty())
        return (splittedParams);

    for (it = params.begin(); it != params.end(); ++it)
    {
        result += *it; // copie each charactere to result
        if (*it == whitespace || (it + 1) == params.end())
        {
                if (*it == whitespace)
                    result.erase(result.size() - 1); // remove whitespace at the end of result
                splittedParams.push_back(result); // add result to the vector
                result.clear(); // empty string result
        };
    }
    return (splittedParams);
}

std::string toUpper( std::string str ) {

    std::string::iterator   it;
    std::string             upperCaseStr;

    if ( str.empty() )
        return (str);
    
    for (it = str.begin(); it != str.end(); it++)
        upperCaseStr += toupper(*it);
    
    std::cout << "toUpperCase = " << upperCaseStr << std::endl;

    return (upperCaseStr);
}

bool    isACommand(std::string buffer)
{
    std::string bigBuf = toUpper(buffer);

    if (bigBuf == "NICK" || bigBuf == "USER" || bigBuf == "USERHOST" || bigBuf == "MOTD" || bigBuf == "JOIN" || bigBuf == "PART")
        return (true);

    return (false);
}