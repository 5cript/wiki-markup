#ifndef COMPONENTS_PARSER_SPACE_HPP_INCLUDED
#define COMPONENTS_PARSER_SPACE_HPP_INCLUDED

#include "parser_core.hpp"

namespace WikiMarkdown { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct space_grammar : qi::grammar <Iterator>
    {
        using grammar_result = void;

        space_grammar() : space_grammar::base_type(main, "properties")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			spaces.add(" ", ' ')("\t", '\t');

            main = +spaces;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator> main;

        // Symbols
        qi::symbols<char const, char const> spaces;
    };

} // Parser
} // Components
} // WikiMarkdown


#endif // COMPONENTS_PARSER_SPACE_HPP_INCLUDED
