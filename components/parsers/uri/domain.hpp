#ifndef COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

#include "ipv4.hpp"
#include "ipv6.hpp"
#include "domain_name.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct domain_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        domain_grammar() : domain_grammar::base_type(main, "domain")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

            main =
                    ipv4s                                           [_val = qi::_1]
                |   (
                            qi::char_('[')                          [phoenix::push_back(_val, '[')]
                        >>  ipv6s                                   [_val += qi::_1]
                        >>  qi::char_(']')                          [phoenix::push_back(_val, ']')]
                    )
                |   domain_name                                     [_val = qi::_1]
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        ipv4s_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD ipv4s;
        ipv6s_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD ipv6s;
        domain_name_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD domain_name;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED
