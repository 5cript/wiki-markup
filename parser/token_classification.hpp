#ifndef PARSER_TOKEN_CLASSIFICATION_HPP_INCLUDED
#define PARSER_TOKEN_CLASSIFICATION_HPP_INCLUDED

#include <string>

namespace WikiMarkup
{
    enum class TokenType
    {
        OPERATOR,
        TEXT,
        SPACE
    };

    std::string extractOperatorToken(std::string::const_iterator begin, std::string::const_iterator end);
    std::string extractTextToken(std::string::const_iterator begin, std::string::const_iterator end);
    std::string extractWhitespaceToken(std::string::const_iterator begin, std::string::const_iterator end);
}

#endif // PARSER_TOKEN_CLASSIFICATION_HPP_INCLUDED
