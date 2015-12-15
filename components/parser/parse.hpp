#ifndef COMPONENTS_PARSE_PARSE_HPP_INCLUDED
#define COMPONENTS_PARSE_PARSE_HPP_INCLUDED

#include "parser_core.hpp"

#include <stdexcept>
#include <type_traits>
#include <string>

namespace WikiMarkdown { namespace Components { namespace Parser
{

    template <typename GrammarT, typename CharType = char_type>
    typename GrammarT::grammar_result parse(std::basic_string <CharType> const& text,
                                            bool doThrow = true,
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
                return {};
        }
        else if (iter != end)
        {
            if (!allowPartial)
            {
                if (doThrow)
                    throw std::runtime_error ("quick parsing failed (no exact match)");
                else
                    return {};
            }
            //else success
        }
        // else success
        return parsed;
    }

} // Parser
} // Components
} // WikiMarkdown


#endif // COMPONENTS_PARSE_PARSE_HPP_INCLUDED
