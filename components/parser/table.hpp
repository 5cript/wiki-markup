#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED

#include "../holders/table.hpp"

#include "parser_core.hpp"
#include "properties.hpp"
#include "basic.hpp"

namespace WikiMarkdown { namespace Components { namespace Parser
{
    using namespace Holders;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct table_grammar : qi::grammar <Iterator, TableData()>
    {
        using grammar_result = TableData;

        // Parser
        table_grammar() : table_grammar::base_type(main, "table")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			table_start.name("table_start");
			main.name("table");

            table_start =
                    qi::lit("{|")
                >   (properties | -space)
                >   linebreak
            ;

            main =
                    eps             [_val = TableData()]
                >>  table_start     [at_c <1> (_val) = qi::_1]
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::map <std::string, std::string> > table_start;
        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        properties_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD properties;
    };

} // Parser
} // Components
} // WikiMarkdown


#endif // TABLE_HPP_INCLUDED
