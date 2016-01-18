#ifndef PARSER_PAGE_PARSER_HPP_INCLUDED
#define PARSER_PAGE_PARSER_HPP_INCLUDED

#include "parser_context.hpp"
#include "../page.hpp"

#include <string>

namespace WikiMarkup
{
    class PageParser
    {
    public:
        PageParser(std::string const& page);

        void parse();
        void parseSection();

    private:
        ParserContext ctx_;
        Page page_;
    };
}

#endif // PARSER_PAGE_PARSER_HPP_INCLUDED
