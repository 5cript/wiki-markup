#ifndef PARSER_PAGE_PARSER_HPP_INCLUDED
#define PARSER_PAGE_PARSER_HPP_INCLUDED

#include "../components/components.hpp"
#include "../page.hpp"
#include "../dll.h"

#include "parser_context.hpp"

#include <boost/optional.hpp>

#include <string>

namespace WikiMarkup
{
    class DLL_EXPORT PageParser
    {
    public:
        PageParser(std::string const& page);

        void parse();

        Page getPage();

    private:
        bool parseSection(ParserContext& ctx, std::string const& prePush);

        /**
         *  Separate Markup into text sections.
         */
        void parseSections();

        /**
         *  Parse each text section from "parseSections" and extract links, tables etc.
         */
        void parseTexts();

        /**
         *  Recombine Texts with links to form an image section, if the link is an image
         */
        void collapse();

        /**
         *
         */
        void enrichText();

        boost::optional <Components::Table> tryParseTable(ParserContext& ctx) const;
        boost::optional <Components::Link> tryParseLink(ParserContext& ctx) const;
        boost::optional <Components::CommentText> tryParseComment(ParserContext& ctx) const;

    private:
        Page page_;
        std::string data_;
    };
}

#endif // PARSER_PAGE_PARSER_HPP_INCLUDED
