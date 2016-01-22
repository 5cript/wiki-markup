#include "page_parser.hpp"

#include "parser_context.hpp"
#include "context_navigation.hpp"

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
        : data_(page)
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

        auto const& components = tempPage.getComponents();
        for (auto const& i : components)
        {
            auto* component = i.get();
            std::string raw;

            if (dynamic_cast <Text*> (component) != nullptr)
                raw = dynamic_cast <Text*> (component)->getRaw();
            else if (dynamic_cast <PreformattedText*> (component) != nullptr)
                raw = dynamic_cast <PreformattedText*> (component)->getRaw();
            else
                continue;

            ParserContext ctx(raw);

            // now parse each of the texts for other components.
            while(ctx.hasMoreToRead())
            {
                auto posBackup = ctx.getPosition();

                auto maybeTable = tryParseTable(tempPage, ctx);
                if (maybeTable)
                    std::cout << "yay table\n";
                else
                    std::cout << "naw, no table\n";
            }
        }
    }
//-----------------------------------------------------------------------------------
    boost::optional <Table> PageParser::tryParseTable(Page& page, ParserContext& ctx)
    {
        ContextNavigator navi(&ctx);
        if(!navi.verifyCharSequence('{', '|'))
            return boost::none;

        // table start! :)
        ParserContext seeker = ctx;
        ContextNavigator seekerNav(&seeker);
        seekerNav.findCharSequence('|', '}');

        if (seekerNav.reachedEnd())
            return boost::none; // not table :(

        Table table;
        auto result = table.fromMarkup(seeker.getSlice());
        if (result == ParsingResult::FAIL)
            return boost::none;
        else
            return boost::optional <Table> {table};
    }
//-----------------------------------------------------------------------------------
    void PageParser::parseSections()
    {
        ParserContext ctx(data_);
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

        while (ctx.hasMoreToRead())
        {
            continueParsing = true;

            if (ctx.isStartOfLine())
            {
                char c = ctx.get(PEEK);

                if (c == '=' || c == '-' || c == '*' || c == '#' ||
                    c == ';' || c == ' ')
                {
                    if (parseSection(ctx))
                        pushText();

                    continueParsing = false;
                }
            }

            if (continueParsing)
            {
                currentText.push_back(ctx.get());
            }
        }

        pushText();
    }
//-----------------------------------------------------------------------------------
    bool PageParser::parseSection(ParserContext& ctx)
    {
        auto wasSection = false;
        auto positionBackup = ctx.getPosition();
        char c = ctx.get(PEEK);

        auto partialIsFail = [this, &positionBackup]() -> bool {
            return false;
        };

        auto parseSingleSection = [&](std::string fromWhat, auto section, auto partialBehaviour) {
            auto result = section.fromMarkup(fromWhat);

            bool good = result != ParsingResult::FAIL &&
            (result == ParsingResult::PARTIAL ? partialBehaviour() : true);

            if (!good)
                ctx.setPosition(positionBackup);
            else {
                wasSection = true;
                page_.appendComponent(std::move(section));
            }
        };

        auto accumulateLinesWhile = [&](auto lineCondition) {
            std::string lines = ctx.getLine().get() + "\n";
            do {
                auto line = ctx.getLine(PEEK);
                if (line && !line.get().empty() && lineCondition(line.get())) {
                    lines += line.get() + "\n";
                    ctx.getLine();
                } else {
                    break;
                }
            }
            while (true);
            return lines;
        };

        if (c == '=') {
            // Headers
            parseSingleSection(ctx.getLine().get(), Header{}, partialIsFail);
        } else if (c == '-') {
            // horizontal line
            parseSingleSection(ctx.getLine().get(), HorizontalLine{}, partialIsFail);
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
