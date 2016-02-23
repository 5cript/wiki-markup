#ifndef COMPONENTS_PARSERS_URL_HPP_INCLUDED
#define COMPONENTS_PARSERS_URL_HPP_INCLUDED

#include "../url.hpp"

#include "uri/domain.hpp"
#include "uri/scheme.hpp"
#include "uri/authority.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct url_grammar : qi::grammar <Iterator, Url()>
    {
        using grammar_result = Url;

        url_grammar() : url_grammar::base_type(main, "url")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
            INSTALL_WARNING_HANDLER;

            pchar =
                unreserved | pct_encoded | sub_delims | qi::char_(":@")
            ;

            unreserved =
                qi::alnum | qi::char_("-._~")
            ;

            // not checking correct HEX ENCODING
            pct_encoded =
                qi::char_('%')
            ;

            sub_delims =
                qi::char_("!$&'()*,;=")
            ;

            path =
                (*(pchar)) % '/'
            ;

            query =
               *(pchar | qi::char_("/?"))
            ;

            fragment =
               *(pchar | qi::char_("/?"))
            ;

            main =
                    scheme                          [at_c <0> (_val) = qi::_1]
                >>  ':'
                >>  (
                        (
                                qi::lit("//")
                            >>  authority           [at_c <1> (_val) = qi::_1]
                            >> -(
                                        qi::char_('/')
                                    >>  path        [at_c <2> (_val) = qi::_1]
                                )
                        )
                        |
                        (
                                -qi::char_('/')
                            >>  (
                                        path        [at_c <2> (_val) = qi::_1]
                                    -   qi::char_('/')
                                )
                        )
                    )
                >> -(
                            qi::char_('?')
                        >>  query                   [at_c <3> (_val) = qi::_1]
                    )
                >> -(
                            qi::char_('#')
                        >>  fragment                [at_c <4> (_val) = qi::_1]
                    )
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // RFC 3986
        qi::rule <Iterator, char()> pchar;
        qi::rule <Iterator, char()> unreserved;
        qi::rule <Iterator, char()> pct_encoded;
        qi::rule <Iterator, char()> sub_delims;

        qi::rule <Iterator, std::vector <std::string>()> path;
        qi::rule <Iterator, std::string()> query;
        qi::rule <Iterator, std::string()> fragment;

        // Grammars
        scheme_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD scheme;
        authority_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD authority;

    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URL_HPP_INCLUDED
