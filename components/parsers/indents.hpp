#ifndef INDENTS_HPP_INCLUDED
#define INDENTS_HPP_INCLUDED

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct indents_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        indents_grammar() : indents_grammar::base_type(main, "indents")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

            main =
                *qi::char_;
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

#endif // INDENTS_HPP_INCLUDED
