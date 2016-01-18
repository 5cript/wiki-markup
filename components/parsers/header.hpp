#ifndef COMPONENTS_PARSERS_HEADER_HPP_INCLUDED
#define COMPONENTS_PARSERS_HEADER_HPP_INCLUDED

#include "../header.hpp"

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct header_grammar : qi::grammar <Iterator, Header(), qi::locals <std::string> >
    {
        using grammar_result = Header;

        header_grammar() : header_grammar::base_type(main, "header")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			start %=
                repeat(2, 6)
                [
                    qi::char_('=')
                ]
			;

			end = lit(_r1);

            main =
                    start                                   [_a = qi::_1]
                >> *space
                >  *(qi::char_ - lit(_a))                   [phoenix::push_back(at_c <0> (_val), qi::_1)]
                >   end(_a)
                >> *space
                >>  eps                                     [at_c <1> (_val) = phoenix::size(qi::_a)]
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> start;
        qi::rule <Iterator, void(std::string)> end;

        qi::rule <Iterator, grammar_result(), qi::locals <std::string> > main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_HEADER_HPP_INCLUDED
