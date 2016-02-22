#ifndef COMPONENTS_PARSERS_LIST_HPP_INCLUDED
#define COMPONENTS_PARSERS_LIST_HPP_INCLUDED

#include "../list.hpp"

#include "../../parser/qi_common/parser_core.hpp"
#include "../../parser/qi_common/basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct list_grammar : qi::grammar <Iterator, PlainList(), qi::locals <char>>
    {
        using grammar_result = PlainList;

        list_grammar() : list_grammar::base_type(main, "list")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;
			INSTALL_DEBUG_HANDLER;

			line.name("line");
			listLine.name("listLine");

			line =
                   *space
                >> *(qi::char_ - linebreak)     [phoenix::push_back(_val, qi::_1)]
                >> *space
                >>  linebreak
			;

            // _r1 = top most list type
			listLine =
                    qi::char_(_r1)                  [phoenix::push_back(at_c <0> (_val), qi::_1)]
                >> *(
                            qi::char_('#')
                        |   qi::char_('*')
                        |   qi::char_(';')
                        |   qi::char_(':')
                    )                               [phoenix::push_back(at_c <0> (_val), qi::_1)]
                >   line                            [at_c <1> (_val) = qi::_1]
			;

			main =
                   &(qi::char_('#') | qi::char_('*'))   [_a = qi::_1]
               >   +listLine(_a)                        [phoenix::push_back(_val, qi::_1)]
			;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> line;

        qi::rule <Iterator, ListLine(char)> listLine;
        qi::rule <Iterator, grammar_result(), qi::locals <char>> main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_LIST_HPP_INCLUDED
