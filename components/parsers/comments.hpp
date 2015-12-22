#ifndef COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct comment_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        comment_grammar() : format_grammar::base_type(main, "comments")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			main =

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

#endif // COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
