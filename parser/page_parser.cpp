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
        parseSections();
        parseTexts();
    }
//-----------------------------------------------------------------------------------
    void PageParser::parseTexts()
    {
        Page tempPage = page_;
        // page_.clear();


    }
//-----------------------------------------------------------------------------------
    void PageParser::parseSections()
    {
        std::string currentText;
        bool continueParsing;

        auto pushText = [&]() {
            if (currentText.empty())
                return;

            Text tex;
            tex.fromMarkup(currentText);
            page_.appendComponent(std::move(tex));
            currentText = "";
        };

        while (ctx_.hasMoreToRead())
        {
            continueParsing = true;

            if (ctx_.isStartOfLine())
            {
                pushText();

                char c = ctx_.get(PEEK);

                if (c == '=' || c == '-' || c == '*' || c == '#' ||
                    c == ';' || c == ' ')
                {
                    parseSection();
                    continueParsing = false;
                }
            }

            if (continueParsing)
            {
                currentText.push_back(ctx_.get());
            }
        }

        pushText();
    }
//-----------------------------------------------------------------------------------
    bool PageParser::parseSection()
    {
        auto wasSection = false;
        auto positionBackup = ctx_.getPosition();
        char c = ctx_.get(PEEK);

        auto partialIsFail = [this, &positionBackup]() -> bool {
            return false;
        };

        auto parseSingleSection = [&](std::string fromWhat, auto section, auto partialBehaviour) {
            auto result = section.fromMarkup(fromWhat);

            bool good = result != ParsingResult::FAIL &&
            (result == ParsingResult::PARTIAL ? partialBehaviour() : true);

            if (!good)
                ctx_.setPosition(positionBackup);
            else {
                wasSection = true;
                page_.appendComponent(std::move(section));
            }
        };

        auto accumulateLinesWhile = [&](auto lineCondition) {
            std::string lines = ctx_.getLine().get() + "\n";
            do {
                auto line = ctx_.getLine(PEEK);
                if (line && !line.get().empty() && lineCondition(line.get())) {
                    lines += line.get() + "\n";
                    ctx_.getLine();
                } else {
                    break;
                }
            }
            while (true);
            return lines;
        };

        if (c == '=') {
            // Headers
            parseSingleSection(ctx_.getLine().get(), Header{}, partialIsFail);
        } else if (c == '-') {
            // horizontal line
            parseSingleSection(ctx_.getLine().get(), HorizontalLine{}, partialIsFail);
        } else if (c == '*' || c == '#') {
            // bullet list || numbered list
            std::string lines = accumulateLinesWhile([c](std::string const& line) {
                return line.front() == c;
            });

            parseSingleSection(lines, List{}, partialIsFail);
        } else if (c == ';') {
            // definition list
        } else if (std::isspace(c)) {
            // preformatted text (remove leading space)
            std::string lines = accumulateLinesWhile([](std::string const& line) {
                return std::isspace(line.front());
            });

            parseSingleSection(lines, PreformattedText{}, partialIsFail);
        }
        return wasSection;
    }
//-----------------------------------------------------------------------------------
    Page PageParser::getPage()
    {
        return page_;
    }
//####################################################################################
}
