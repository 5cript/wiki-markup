#include "token.hpp"

namespace WikiMarkup
{
//####################################################################################
    std::size_t DLL_EXPORT Token::getStartPosition() const
    {
        return startPosition_;
    }
//-----------------------------------------------------------------------------------
    std::size_t DLL_EXPORT Token::getEndPosition() const
    {
        return endPosition_;
    }
//-----------------------------------------------------------------------------------
    std::string DLL_EXPORT Token::getData() const
    {
        return data_;
    }
//-----------------------------------------------------------------------------------
    TokenType DLL_EXPORT Token::getType() const
    {
        return type_;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT Token::Token()
        : startPosition_{}
        , endPosition_{}
        , data_{}
        , type_{}
    {

    }
//####################################################################################
    boost::optional <Token> DLL_EXPORT extractToken(std::string::const_iterator begin,
                                         std::string::const_iterator& position,
                                         std::string::const_iterator end)
    {
        Token tok;
        auto prepareToken = [&](std::string const& data, TokenType type) {
            tok.data_ = data;
            tok.startPosition_ = position - begin;
            tok.endPosition_ = tok.startPosition_ + data.length();
            tok.type_ = type;

            position += tok.endPosition_ - tok.startPosition_;
        };

        if (position >= end)
            return boost::none;

        std::string tokenData;

        // operator token
        tokenData = extractOperatorToken(position, end);
        if (!tokenData.empty())
        {
            prepareToken(tokenData, TokenType::OPERATOR);
            return tok;
        }

        // text token
        tokenData = extractTextToken(position, end);
        if (!tokenData.empty())
        {
            prepareToken(tokenData, TokenType::TEXT);
            return tok;
        }

        // space token
        tokenData = extractWhitespaceToken(position, end);
        if (!tokenData.empty())
        {
            prepareToken(tokenData, TokenType::SPACE);
            return tok;
        }

        return boost::none;
    }
//####################################################################################
}
