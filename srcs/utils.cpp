#include "utils.hpp"
#include <unistd.h>
#include <signal.h>

void   sendError( std::string message ) {
    std::cerr << message << std::endl;
}

// void sigintHandler(int sig) {
//         (void)sig;
//         // Affiche un message et termine proprement le processus
//         std::cout << "SIGINT reçu, arrêt du programme" << std::endl;
//         // //ok gros tej les trucs pour eviter que ca leak;
//         // tej tous les users;
//         // tej le server;
//         exit(0);
// }

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

void splitStringSep(std::vector<std::string>    &params, std::string sep )
{
    std::string                     tmp;
    size_t                          startPos = 0;
    size_t                          endPos = 0;
    int                             sepLength = sep.length();
    std::string                     result;

    if (params.empty())
        return;
    tmp = params.at(0);
    params.clear();
    while ((endPos = tmp.find(sep, startPos)) != std::string::npos)
    {
        result = tmp.substr(startPos, endPos - startPos); // on substr juste avant \r\n
        std::cout << "Splitted String Sep result = " << result << std::endl;
        startPos = endPos + sepLength; // on avance startPos apres \r\n
        params.push_back(result); // on ajoute notre str au vector
        result.clear();
    }
    tmp.clear();
}

std::vector<std::string> splitString( std::string params )
 {

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

bool    isACommand(std::string buffer, Server& server)
{
    if (buffer.empty() || server.getCommandMap().empty())
        return (false);
    
    displayMap(server.getCommandMap(),"commandMap");
    
    std::string bigBuf = toUpper(buffer);
    std::map<std::string, void (*)(std::string params, User &user)>::iterator   it;

    for (it = server.getCommandMap().begin(); it != server.getCommandMap().end(); it++)
    {
        if (it->first == bigBuf)
            return (true);
    }

    return (false);
}

bool    isInVectorList( std::string target, std::vector<std::string> stringVector )
{
    std::vector<std::string>::iterator   it;

    for (it = stringVector.begin(); it != stringVector.end(); it++)
    {
        if (*it == target)
        {
            std::cout << "isInVectorList : " << *it << " = " << target << std::endl;
            return (true);
        }
    }
    std::cout << "isInVectorList : " << target << " -> Not found !" << std::endl;
    return (false);
}

template <class T, class U>
void    displayMap(const std::map<T, U>& map, const std::string& name)
{
    for (typename std::map<T, U>::const_iterator it = map.begin(); it != map.end(); it++)
    {
        std::cout << name << "[" << it->first << "] = " << it->second << std::endl;
    }
}