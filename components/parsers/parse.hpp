#ifndef COMPONENTS_PARSE_PARSE_HPP_INCLUDED
#define COMPONENTS_PARSE_PARSE_HPP_INCLUDED

#include "parser_core.hpp"
#include "parsing_results.hpp"

#include <stdexcept>
#include <type_traits>
#include <string>
#include <utility>

namespace WikiMarkup { namespace Components { namespace Parser
{

    template <typename GrammarT, typename CharType = char_type>
        std::pair <ParsingResult, typename GrammarT::grammar_result>
        parse(std::basic_string <CharType> const& text,
              bool doThrow = false,
              bool allowPartial = true)
    {
        using encoding::space;

        GrammarT grammar;
        typename GrammarT::grammar_result parsed;

        auto iter = std::cbegin(text);
        auto end = std::cend(text);

        //static_assert (std::is_same <decltype(iter), std::wstring::const_iterator>::value, "");

        bool result = qi::phrase_parse (iter, end, grammar, space, parsed);

        if (!result)
        {
            if (doThrow)
                throw std::runtime_error ("quick parsing failed");
            else
                return std::make_pair(ParsingResult::FAIL, typename GrammarT::grammar_result{});
        }
        else if (iter != end)
        {
            if (!allowPartial)
            {
                if (doThrow)
                    throw std::runtime_error ("quick parsing failed (no exact match)");
                else
                    return std::make_pair(ParsingResult::FAIL, typename GrammarT::grammar_result{});
            }
            return std::make_pair(ParsingResult::PARTIAL, typename GrammarT::grammar_result{});
        }
        return std::make_pair(ParsingResult::FULL_SUCCESS, parsed);
    }

} // Parser
} // Components
} // WikiMarkup

#define TYPEDEF_GRAMMAR(NAME) \
using grammar = WikiMarkup::Components::Parser::NAME < \
    qi_error::error_handler_cerr, \
    qi_error::warning_handler_cout, \
    std::string::const_iterator \
>


#endif // COMPONENTS_PARSE_PARSE_HPP_INCLUDED
