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

        Page getPage();

    private:
        bool parseSection();
        void parseSections();

    private:
        ParserContext ctx_;
        Page page_;
    };
}

#endif // PARSER_PAGE_PARSER_HPP_INCLUDED
