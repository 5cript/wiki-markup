#include "page_parser.hpp"

#include "parser_context.hpp"
#include "../components/components.hpp"

#include <iostream>

#define PEEK true // for readability

namespace WikiMarkup
{
//####################################################################################
    using namespace Components;
    using namespace std::string_literals;
//-----------------------------------------------------------------------------------
    PageParser::PageParser(std::string const& page)
        : ctx_(page)
    {

    }
//-----------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
    void PageParser::parseSection()
    {
        auto positionBackup = ctx_.getPosition();
        char c = ctx_.get(PEEK);

        // section formatting
        if (c == '=') {
            Header head;
            auto result = head.fromMarkup(ctx_.getLine().get());

            if (result == ParsingResult::PARTIAL ||
                result == ParsingResult::FAIL)
            {
                // not a header
                ctx_.setPosition(positionBackup);
            }
            else
            {
                page_.appendComponent(std::move(head));
            }
        } else if (c == '-') {
            HorizontalLine hLine;
            auto result = hLine.fromMarkup(ctx_.getLine().get());

            if (result == ParsingResult::PARTIAL ||
                result == ParsingResult::FAIL)
            {
                // not a h-line
                ctx_.setPosition(positionBackup);
            }
            else
            {
                page_.appendComponent(std::move(hLine));
            }
            // horizontal line
        } else if (c == '*' || c == '#') {
            std::string lines = ctx_.getLine().get() + "\n";
            do {
                auto line = ctx_.getLine(PEEK);
                if (line && !line.get().empty() && line.get().front() == c) {
                    lines += line.get() + "\n";
                    ctx_.getLine(); // move forward
                } else {
                    break;
                }
            }
            while (true);

            List list;
            auto result = list.fromMarkup(lines);

            if (result == ParsingResult::PARTIAL ||
                result == ParsingResult::FAIL)
            {
                // not a list
                ctx_.setPosition(positionBackup);
            }
            else
            {
                page_.appendComponent(std::move(list));
            }
            // bullet list || numbered list
        } else if (c == ';') {
            // definition list
        } else if (c == ' ') {
            // preformatted text (remove leading space)
        }
    }
//-----------------------------------------------------------------------------------
    Page PageParser::getPage()
    {
        return page_;
    }
//####################################################################################
}
