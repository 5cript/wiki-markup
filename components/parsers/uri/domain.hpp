#ifndef COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED

#include "../parser_core.hpp"
#include "../basic.hpp"

#include "ipv4.hpp"
#include "ipv6.hpp"
#include "domain_name.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct domain_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        domain_grammar() : domain_grammar::base_type(main, "domain")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

            main =
                    ipv4s
                |   (qi::char_("[") >> ipv6 >> qi::char_("]"))
                |   domain_name
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        ipv4_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD ipv4s;
        ipv6_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD ipv6;
        domain_name_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD domain_name;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_DOMAIN_HPP_INCLUDED
