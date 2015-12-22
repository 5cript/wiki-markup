#ifndef COMPONENTS_PARSERS_LIST_HPP_INCLUDED
#define COMPONENTS_PARSERS_LIST_HPP_INCLUDED

#include "../list.hpp"

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct list_grammar : qi::grammar <Iterator, List(), qi::locals <std::string, List> >
    {
        using grammar_result = List;

        list_grammar() : list_grammar::base_type(main, "list")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;
			INSTALL_DEBUG_HANDLER;

			line.name("line");
			list.name("list");

			line =
                   *space
                >> *(qi::char_ - linebreak)     [phoenix::push_back(_val, qi::_1)]
                >> *space
                >>  linebreak
			;

			list =
                    eps
                    [
                        at_c <2> (_val) = at_c <2> (_r2)
                    ]
                >>  ((
                            lit(_r1)    [dout("lit_r1")]
                        >>  (
                                (
                                        qi::char_('#')              [at_c <2> (_val) = LT_NUMBERED, dout("numbered")]
                                    |   qi::char_('*')              [at_c <2> (_val) = LT_BULLET, dout("bullet")]
                                    |   qi::char_(':')              [at_c <2> (_val) = LT_INDENT, dout("indent")]
                                )                                   [phoenix::push_back(_r1, qi::_1), _a = 0, dout("push")]
                                |
                                eps
                                [
                                    _a = 1, dout("no change")
                                ]
                            )
                        >   line                                    [at_c <3> (_val) = qi::_1, dout("line")]
                        >  -list(_r1, _val)
                            [
                                if_(_a == 0)
                                [
                                    phoenix::push_back(at_c <0> (_val), qi::_1)
                                ].else_
                                [
                                    phoenix::push_back(at_c <1> (_val), qi::_1)
                                ]

                            ] // push back is HACK!
                    )
                    |
                    (
                            eps
                            [
                                phoenix::pop_back(_r1), dout("pop"),
                                if_(phoenix::empty(_r1))
                                [
                                    _pass = false
                                ]
                            ]
                        >>  list(_r1, _val)                         [phoenix::push_back(at_c <0> (_val), qi::_1), dout("out")] // push back is HACK!
                    ))
			;

			main %=
                list(_a, _b)
			;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> line;

        qi::rule <Iterator, List(std::string, List), qi::locals <int> > list;
        qi::rule <Iterator, grammar_result(), qi::locals <std::string, List> > main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_LIST_HPP_INCLUDED
