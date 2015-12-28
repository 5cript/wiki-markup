#ifndef DOMAIN_NAME_HPP_INCLUDED
#define DOMAIN_NAME_HPP_INCLUDED

#include "../parser_core.hpp"
#include "../basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct domain_name_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        domain_name_grammar() : domain_name_grammar::base_type(main, "domain_name")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

            main =
               +(qi::alnum | qi::char_('.') | qi::char_('-'))
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // DOMAIN_NAME_HPP_INCLUDED
