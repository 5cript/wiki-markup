#ifndef INDENTS_HPP_INCLUDED
#define INDENTS_HPP_INCLUDED

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct indents_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        indents_grammar() : indents_grammar::base_type(main, "indents")
        {
            using namespace common_usings;

            main =
                   *qi::char_(':')                          [phoenix::push_back(_val, '\t')]
                >> *space
                >>  qi::char_                               [phoenix::push_back(_val, qi::_1)]
            ;
        }

        // Rules

        qi::rule <Iterator, grammar_result()> main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // INDENTS_HPP_INCLUDED
