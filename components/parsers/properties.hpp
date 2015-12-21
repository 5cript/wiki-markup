#ifndef COMPONENTS_PARSER_PROPERTIES_HPP_INCLUDED
#define COMPONENTS_PARSER_PROPERTIES_HPP_INCLUDED

#include "parser_core.hpp"
#include "basic.hpp"
#include "unescaped_string.hpp"

#include <utility>
#include <map>
#include <string>

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct properties_grammar : qi::grammar <Iterator, std::map<std::string, std::string>()>
    {
        using grammar_result = std::map<std::string, std::string>;

        // Parser
        properties_grammar() : properties_grammar::base_type(main, "properties")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			key.name("key");
			value.name("value");
			property.name("property");

            key %=
                qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9")
            ;

            value = unescaped;

			property %=
                    key
                >>  '='
                >>  value
			;

            main %=
                property >> *(+space >> property)
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> key;
        qi::rule <Iterator, std::string()> value;
        qi::rule <Iterator, std::pair <std::string, std::string>()> property;
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        unescaped_string_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD unescaped;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSER_PROPERTIES_HPP_INCLUDED
