#ifndef PARSER_PAGE_PARSER_HPP_INCLUDED
#define PARSER_PAGE_PARSER_HPP_INCLUDED

#include "../components/components.hpp"
#include "parser_context.hpp"
#include "../page.hpp"

#include <boost/optional.hpp>

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
        bool parseSection(ParserContext& ctx);
        void parseSections();
        void parseTexts();

        boost::optional <Components::Table> tryParseTable(Page& page, ParserContext& ctx);

    private:
        Page page_;
        std::string data_;
    };
}

#endif // PARSER_PAGE_PARSER_HPP_INCLUDED
