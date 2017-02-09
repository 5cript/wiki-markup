#ifndef PARSER_PARSER_CONTEXT_HPP_INCLUDED
#define PARSER_PARSER_CONTEXT_HPP_INCLUDED

#include <string>
#include <vector>

#include "token.hpp"

#ifndef PEEK
#   define PEEK true
#endif

namespace WikiMarkup
{
    struct DLL_EXPORT Line
    {
        std::string data;
        std::size_t start;
        std::size_t end;
    };

    class DLL_EXPORT ParserContext
    {
    public:
        using position_type = std::size_t;
        using size_type = std::size_t;

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
        char get(bool peek = false) const noexcept;

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
        position_type getPosition() const noexcept;

        /**
         *  Sets the current parser position
         */
        void setPosition(position_type position) noexcept;

        /**
         *  Shifts the position forward by 'amount' characters.
         *  Sets position to end if position+amount > end.
         */
        void forwardPosition(position_type amount) noexcept;

        /**
         *  Returns true if the current position is the start of a line.
         */
        bool isStartOfLine() const;

        /**
         *  Returns true if position != end.
         */
        bool hasMoreToRead() const noexcept;

        /**
         *  Moves the position forwards.
         */
        ParserContext& operator++() noexcept;

        /**
         *  Moves the position forwards.
         */
        ParserContext operator++(int) noexcept;

        /**
         *  Moves the position forwards.
         */
        ParserContext& operator--() noexcept;

        /**
         *  Moves the position forwards.
         */
        ParserContext operator--(int) noexcept;

        /**
         *  Takes all the remaining characters in the context, after the position, and returns them.
         *  @return Returns all after position.
         */
        std::string getSlice() const;

        /**
         *  setPosition(end of input);
         */
        void setCursorToEnd();

    private:
        void tokenize();
        void splitLines();

    private:
        std::string page_;
        mutable position_type position_;
        std::vector <Line> lines_;
        std::vector <Token> tokens_;
    };
}

#endif // PARSER_PARSER_CONTEXT_HPP_INCLUDED
