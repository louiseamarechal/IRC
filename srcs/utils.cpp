/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:53:19 by jbouyer           #+#    #+#             */
/*   Updated: 2023/03/02 13:57:02 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <unistd.h>
#include <signal.h>

void   sendError( std::string message ) {
    std::cerr << message << std::endl;
}

std::string  createMessage(  std::vector<std::string> splittedParams )
{
    std::string message;

    if (splittedParams.size() == 2)
    {
        message = splittedParams[1];
        return (message);
    }

    for (size_t i = 1; i < splittedParams.size(); i++)
        message += splittedParams[i] + " ";

    return (message);
}

std::string removeConsecutiveWhitespace( std::string buffer ) {

    char                    whitespace = 32;
    std::string             result;
    std::string::iterator   it = buffer.begin();
    
    if (buffer.empty())
        return (buffer);

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
    if (tmp.find(sep, startPos) == std::string::npos)
    {
        params.push_back(tmp);
        return ;
    }
    params.clear();
    while ((endPos = tmp.find(sep, startPos)) != std::string::npos)
    {
        result = tmp.substr(startPos, endPos - startPos); // on substr juste avant \r\n
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
    
    return (upperCaseStr);
}

bool    isACommand(std::string buffer, Server& server)
{
    if (buffer.empty() || server.getCommandMap().empty())
        return (false);

    std::string bigBuf = toUpper(buffer);
    std::map<std::string, void (*)(std::string params, User &user)>::const_iterator   it;

    if (bigBuf == "MODE")
        return (true);
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
            return (true);
    }
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

void    printVector( std::vector<std::string> vector, std::string vectorName )
{
    std::cout << vectorName << " : " << std::endl;
    for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
        std::cout << "\t- " << *it << std::endl;
}