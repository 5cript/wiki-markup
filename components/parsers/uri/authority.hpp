#ifndef COMPONENTS_PARSERS_URI_AUTHORITY_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_AUTHORITY_HPP_INCLUDED

#include "../parser_core.hpp"
#include "../basic.hpp"

#include "domain.hpp"
#include "../../url.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct authority_grammar : qi::grammar <Iterator, Authority()>
    {
        using grammar_result = Authority;

        authority_grammar() : authority_grammar::base_type(main, "authority")
        {
            using namespace common_usings;
            using namespace Rules;

            user %=
               *(qi::char_ - qi::char_(':'))
            ;

            password %=
               *(qi::char_ - qi::char_('@'))
            ;

            auth =
                    user                        [at_c <0> (_val) = qi::_1]
                >>  ':'
                >>  password                    [at_c <1> (_val) = qi::_1]
                >>  '@'
            ;

            host =
                domain
            ;

            port =
                qi::ushort_
            ;

            main =
                   -auth
                    [
                        at_c <0> (_val) = at_c <0> (qi::_1),
                        at_c <1> (_val) = at_c <1> (qi::_1)
                    ]
                >>  host                        [at_c <2> (_val) = qi::_1]
                >> -(
                            qi::char_(':')
                        >>  port                [at_c <3> (_val) = qi::_1]
                    )
            ;
        };

        // Rules
        qi::rule <Iterator, std::string()> user;
        qi::rule <Iterator, std::string()> password;
        qi::rule <Iterator, boost::fusion::vector <std::string, std::string>()> auth;
        qi::rule <Iterator, std::string()> host;
        qi::rule <Iterator, uint16_t> port;
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        domain_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD domain;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_AUTHORITY_HPP_INCLUDED
