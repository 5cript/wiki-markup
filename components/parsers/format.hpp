#ifndef COMPONENTS_PARSERS_FORMAT_HPP_INCLUDED
#define COMPONENTS_PARSERS_FORMAT_HPP_INCLUDED

#include "../format.hpp"

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct format_grammar : qi::grammar <Iterator, std::vector <FormattedString>()>
    {
        using grammar_result = std::vector <FormattedString>;

        format_grammar() : format_grammar::base_type(main, "format")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			fat_italic_strike =
               *(
                    (
                        lit("'''")
                        [
                            phoenix::push_back(_b, _a),
                            phoenix::clear(at_c <0> (_a)),
                            at_c <1> (_a) = !at_c <1> (_a)
                        ]
                    )
                    |
                    (
                        lit("''")
                        [
                            phoenix::push_back(_b, _a),
                            phoenix::clear(at_c <0> (_a)),
                            at_c <2> (_a) = !at_c <2> (_a)
                        ]
                    )
                    |
                    (
                        lit("<strike>")
                        [
                            if_(at_c <3> (_a))
                            [
                                at_c <0>(_a) += "<strike>"
                            ]
                            .else_
                            [
                                phoenix::push_back(_b, _a),
                                phoenix::clear(at_c <0> (_a)),
                                at_c <3> (_a) = true
                            ]
                        ]
                    )
                    |
                    (
                        lit("</strike>")
                        [
                            if_(!at_c <3> (_a))
                            [
                                at_c <0>(_a) += "</strike>"
                            ]
                            .else_
                            [
                                phoenix::push_back(_b, _a),
                                phoenix::clear(at_c <0> (_a)),
                                at_c <3> (_a) = false
                            ]
                        ]
                    )
                    |
                    (
                        qi::char_               [phoenix::push_back(at_c <0> (_a), qi::_1)]
                    )
                )
                >> eps [phoenix::push_back(_b, _a)]
                >> eps [_val = _b]
			;

            main %=
                fat_italic_strike
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, grammar_result(), qi::locals <FormattedString, std::vector <FormattedString>> > fat_italic_strike;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_FORMAT_HPP_INCLUDED
