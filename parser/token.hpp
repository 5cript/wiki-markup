#ifndef PARSER_TOKEN_HPP_INCLUDED
#define PARSER_TOKEN_HPP_INCLUDED

#include "token_classification.hpp"

#include <boost/optional.hpp>

namespace WikiMarkup
{
    class Token
    {
        friend boost::optional <Token> extractToken(std::string::const_iterator begin,
                                                    std::string::const_iterator& position,
                                                    std::string::const_iterator end);

    public:
        std::size_t getStartPosition() const;
        std::size_t getEndPosition() const;

        std::string getData() const;
        TokenType getType() const;

    private:
        Token();

        std::size_t startPosition_;
        std::size_t endPosition_;

        std::string data_;
        TokenType type_;
    };

    boost::optional <Token> extractToken(std::string::const_iterator begin,
                                         std::string::const_iterator& position,
                                         std::string::const_iterator end);
}

#endif // PARSER_TOKEN_HPP_INCLUDED
