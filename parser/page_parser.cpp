#include "page_parser.hpp"

#include "parser_context.hpp"
#include "../components/components.hpp"

#include <iostream>

#define PEEK true // for readability

namespace WikiMarkup
{
    using namespace Components;

    PageParser::PageParser(std::string const& page)
        : ctx_(page)
    {

    }

    void PageParser::parse()
    {
        if (ctx_.isStartOfLine()) {
            char c = ctx_.get(PEEK);

            if (c == '=' || c == '-' || c == '*' || c == '#' ||
                c == ';' || c == ' ')
            {
                parseSection();
            }
        }
    }

    void PageParser::parseSection()
    {
        auto positionBackup = ctx_.getPosition();
        char c = ctx_.get(PEEK);

        // section formatting
        if (c == '=') {
            Header head;
            auto result = head.fromMarkup(ctx_.getLine().get());

            if (    result == ParsingResult::PARTIAL
                ||  result == ParsingResult::FAIL)
            {
                // not a header
                ctx_.setPosition(positionBackup);
            }
            else
            {
                page_.appendComponent(head);
            }
        } else if (c == '-') {
            // horizontal line
        } else if (c == '*') {
            // bullet list
        } else if (c == '#') {
            // numbered list
        } else if (c == ';') {
            // definition list
        } else if (c == ' ') {
            // preformatted text (remove leading space)
        }
    }
}
