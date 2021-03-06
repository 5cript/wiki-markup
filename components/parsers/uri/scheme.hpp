#ifndef SCHEME_HPP_INCLUDED
#define SCHEME_HPP_INCLUDED

#include "twisted-spirit/core/parser_core.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct scheme_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::array <uint16_t, 8>;

        scheme_grammar() : scheme_grammar::base_type(main, "scheme")
        {
            using namespace common_usings;

            main =
                    qi::alpha
                >> *(qi::alnum | qi::char_("+.-"))
            ;
        }

        // Rules
        qi::rule <Iterator, std::string()> main;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // SCHEME_HPP_INCLUDED
