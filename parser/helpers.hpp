#ifndef PARSER_HELPERS_HPP_INCLUDED
#define PARSER_HELPERS_HPP_INCLUDED

#include <cctype>

namespace WikiMarkup
{
    /*
        Definition of whitespace might change
     */
    bool isWhitespace(char c)
    {
        return std::isspace(c);
    }
}

#endif // PARSER_HELPERS_HPP_INCLUDED
