#include "page_parser.hpp"

#include "parser_context.hpp"
#include "context_navigation.hpp"
#include "../configuration.hpp"

#include <iostream>

namespace WikiMarkup
{
//###################################################################################
    using namespace Components;
//###################################################################################
    template <typename PageT>
    void pushText(PageT& page, std::string const& prePush)
    {
        Text tex;
        tex.fromMarkup(prePush);
        page.appendComponent(std::move(tex));
    }
//-----------------------------------------------------------------------------------
    template <typename ContextT, typename PositionT, typename SectionT, typename FuncT, typename PageT>
    void parseSingleSection(std::string fromWhat, std::string const& prePush, ContextT& ctx,
                            PositionT& positionBackup, PageT& page, bool& wasSection, SectionT section, FuncT partialBehaviour)
    {
        auto result = section.fromMarkup(fromWhat);

        bool good = result != ParsingResult::FAIL &&
        (result == ParsingResult::PARTIAL ? partialBehaviour() : true);

        if (!good)
            ctx.setPosition(positionBackup);
        else {
            wasSection = true;
            pushText(page, prePush);
            page.appendComponent(std::move(section));
        }
    }
//-----------------------------------------------------------------------------------
    void forwardByParsingResult(ParserContext& ctx, TwistedSpirit::ParsingResult result)
    {
        if (result == TwistedSpirit::ParsingResult::FULL_SUCCESS)
            ctx.setCursorToEnd();
        else
            ctx.forwardPosition(static_cast <ParserContext::position_type> (result));
    }
//###################################################################################
    /**
     *  Used internally. Extracted to reduce function length.
     */
    void pushTextToPage(std::string& accumText, Page& page)
    {
        if (accumText.empty())
            return;

        Text tex;
        tex.fromMarkup(accumText);
        page.appendComponent(std::move(tex));
        accumText = "";
    }
//-----------------------------------------------------------------------------------
    /**
     *  Used internally. Extracted to reduce function length.
     */
    template <typename T>
    bool finalizeSpecialComponent(boost::optional <T> const& component, std::string& accumText, Page& page)
    {
        if (!component)
            return false;

        pushTextToPage(accumText, page);
        page.appendComponent(component.get());
        return true;
    }
//###################################################################################
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
        page_.clear();

        auto const& components = tempPage.getComponents();
        for (auto const& i : components)
        {
            auto* component = i.get();
            std::string raw;

            if (dynamic_cast <Text*> (component) != nullptr)
                raw = dynamic_cast <Text*> (component)->getRaw();
            else if (dynamic_cast <PreformattedText*> (component) != nullptr)
                raw = dynamic_cast <PreformattedText*> (component)->getRaw();
            else {
                page_.appendComponent(*i);
                continue;
            }

            // A parser context for this text component.
            ParserContext ctx(raw);
            std::string textAccum;

            // now parse each of the texts for other components.
            while(ctx.hasMoreToRead())
            {
                // Tables
                auto table = tryParseTable(ctx);
                if (finalizeSpecialComponent(table, textAccum, page_))
                    continue;

                // Links
                auto link = tryParseLink(ctx);
                if (finalizeSpecialComponent(link, textAccum, page_))
                    continue;
                else if (ctx.get(PEEK) == '[')
                    textAccum.push_back(ctx.get()); // to ignore erroneous links. we want them as text.

                // Comments
                auto comment = tryParseComment(ctx);
                if (finalizeSpecialComponent(comment, textAccum, page_))
                    continue;

                // Otherwise (so it REALLY is text, huh?)
                textAccum.push_back(ctx.get());
            }
            pushTextToPage(textAccum, page_);
        }

        tempPage.dumpComponentNames(std::cout) << "\n";
        page_.dumpComponentNames(std::cout) << "\n";
    }
//-----------------------------------------------------------------------------------
    boost::optional <Table> PageParser::tryParseTable(ParserContext& ctx) const
    {
        ContextNavigator navi(&ctx);
        if(!navi.verifyCharSequence('{', '|'))
            return boost::none;

        Table table;
        auto result = table.fromMarkup(ctx.getSlice());
        if (result == ParsingResult::FAIL)
            return boost::none;

        forwardByParsingResult(ctx, result);

        return boost::optional <Table> {table};
    }
//-----------------------------------------------------------------------------------
    boost::optional <Components::Link> PageParser::tryParseLink(ParserContext& ctx) const
    {
        ContextNavigator navi(&ctx);
        // check for implicit external:
        auto config = Configuration::getInstance().getReadOnly();
        bool foundImplicit = false;
        for (auto const& i : config.urlProtocols)
        {
            if (navi.verifyCharSequence(i))
            {
                foundImplicit = true;
                break;
            }
        }

        // any type of link, that is not an implicit external link, must start with a [
        if (!foundImplicit && ctx.get(PEEK) != '[' && !navi.verifyCharSequence("#REDIRECT"))
            return boost::none;

        Link link;
        auto result = link.fromMarkup(ctx.getSlice());
        if (result == ParsingResult::FAIL)
            return boost::none;

        forwardByParsingResult(ctx, result);

        return boost::optional <Link> {link};
    }
//-----------------------------------------------------------------------------------
    boost::optional <Components::CommentText> PageParser::tryParseComment(ParserContext& ctx) const
    {
        ContextNavigator navi(&ctx);
        if (!navi.verifyCharSequence("<!--"))
            return boost::none;

        CommentText comment;
        auto result = comment.fromMarkup(ctx.getSlice());
        if (result == ParsingResult::FAIL)
            return boost::none;

        forwardByParsingResult(ctx, result);

        return boost::optional <CommentText> {comment};
    }
//-----------------------------------------------------------------------------------
    void PageParser::parseSections()
    {
        ParserContext ctx(data_);
        std::string currentText;
        bool continueParsing;

        while (ctx.hasMoreToRead())
        {
            continueParsing = true;

            if (ctx.isStartOfLine())
            {
                char c = ctx.get(PEEK);

                if (c == '=' || c == '-' || c == '*' || c == '#' ||
                    c == ';' || c == ' ')
                {
                    if (parseSection(ctx, currentText))
                        currentText.clear();

                    continueParsing = false;
                }
            }

            if (continueParsing)
            {
                currentText.push_back(ctx.get());
            }
        }

        Text tex;
        tex.fromMarkup(currentText);
        page_.appendComponent(std::move(tex));
    }
//-----------------------------------------------------------------------------------
    bool PageParser::parseSection(ParserContext& ctx, std::string const& prePush)
    {
        auto wasSection = false;
        auto positionBackup = ctx.getPosition();
        char c = ctx.get(PEEK);

        auto partialIsFail = [this, &positionBackup]() -> bool {
            return false;
        };

        auto accumulateLinesWhile = [&](std::function <bool(std::string const&)> lineCondition) {
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

        #define NO_CPP_14_LAMBDA_WORK_AROUND \
            prePush, ctx, positionBackup, page_, wasSection

        if (c == '=') {
            // headers
            parseSingleSection(ctx.getLine().get(), NO_CPP_14_LAMBDA_WORK_AROUND, Header{}, partialIsFail);
        } else if (c == '-') {
            // horizontal line
            parseSingleSection(ctx.getLine().get(), NO_CPP_14_LAMBDA_WORK_AROUND, HorizontalLine{}, partialIsFail);
        } else if (c == '*' || c == '#') {
            // bullet list || numbered list
            std::string lines = accumulateLinesWhile([c](std::string const& line) {
                return line.front() == c;
            });

            parseSingleSection(lines, NO_CPP_14_LAMBDA_WORK_AROUND, List{}, partialIsFail);
        } else if (c == ';') {
            // definition list
        } else if (std::isspace(c)) {
            // preformatted text (remove leading space)
            std::string lines = accumulateLinesWhile([](std::string const& line) {
                return std::isspace(line.front());
            });

            parseSingleSection(lines, NO_CPP_14_LAMBDA_WORK_AROUND, PreformattedText{}, partialIsFail);
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
