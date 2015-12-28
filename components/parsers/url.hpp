#ifndef COMPONENTS_PARSERS_URL_HPP_INCLUDED
#define COMPONENTS_PARSERS_URL_HPP_INCLUDED

#include "../url.hpp"

#include "uri/domain.hpp"
#include "uri/scheme.hpp"

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct url_grammar : qi::grammar <Iterator, Url()>
    {
        using grammar_result = Url;

        url_grammar() : url_grammar::base_type(main, "url")
        {
            using namespace common_usings;

            main =
                    scheme              [at_c <0> (_val) = qi::_1]
                >>  domain              [at_c <1> (_val) = qi::_1]
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        scheme_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD scheme;
        domain_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD domain;

    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URL_HPP_INCLUDED
