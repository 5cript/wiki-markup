#ifndef PARSER_PARSER_CONTEXT_HPP_INCLUDED
#define PARSER_PARSER_CONTEXT_HPP_INCLUDED

#include <string>
#include <vector>

#include "token.hpp"

namespace WikiMarkup
{
    struct Line
    {
        std::string data;
        std::size_t start;
        std::size_t end;
    };

    class ParserContext
    {
    public:
        /**
         *  Prepares the page and converts it into multiple different useful
         *  formats for parsing (lines, tokens, plain).
         *
         *  @param page The wikipage in raw text.
         */
        ParserContext(std::string page);

        /**
         *  Returns a character and increments the position by one.
         *  Returns '\0' if there is no more character to read.
         *
         *  @param peek Does not forward the position, if true.
         */
        char get(bool peek = false) const;

        /**
         *  Reads the current line up to the end (consumes CR, LF),
         *  but returns the whole line.
         *
         *  @param peek Does not forward the position, if true.
         */
        boost::optional <std::string> getLine(bool peek = false) const;

        /**
         *  Returns the current token we are positioned on, if the end was not reached.
         *
         *  @param peek Does not forward the position, if true.
         */
        boost::optional <Token> getToken(bool peek = false) const;

        /**
         *  Returns the current position in the page text.
         */
        std::size_t getPosition() const;

        /**
         *  Sets the current parser position
         */
        void setPosition(std::size_t position);

        /**
         *  Returns true if the current position is the start of a line.
         */
        bool isStartOfLine() const;

        /**
         *  Returns true if position != end.
         */
        bool hasMoreToRead() const;

        /**
         *  Moves the position forwards.
         */
        ParserContext& operator++();

        /**
         *  Moves the position forwards.
         */
        ParserContext operator++(int);

        /**
         *  Moves the position forwards.
         */
        ParserContext& operator--();

        /**
         *  Moves the position forwards.
         */
        ParserContext operator--(int);

    private:
        void tokenize();
        void splitLines();

    private:
        std::string page_;
        mutable std::size_t position_;
        std::vector <Line> lines_;
        std::vector <Token> tokens_;
    };
}

#endif // PARSER_PARSER_CONTEXT_HPP_INCLUDED
