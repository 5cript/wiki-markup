#ifndef COMPONENTS_PARSERS_TABLE_HPP_INCLUDED
#define COMPONENTS_PARSERS_TABLE_HPP_INCLUDED

#include "../table.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"
#include "properties.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct table_grammar : qi::grammar <Iterator, Table()>
    {
        using grammar_result = Table;

        table_grammar() : table_grammar::base_type(main, "table")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			table_start.name("table_start");
			table_end.name("table_end");
			table_caption.name("table_caption");
			table_cell.name("table_cell");
			table_cells.name("table_cells");
			table_header_cell.name("table_header_cell");
			table_row.name("table_row");
			table_rows.name("table_rows");
			just_pipe.name("just_pipe");

            just_pipe =
                qi::char_('|') - qi::lit("|+") - qi::lit("|-") - qi::lit("|}")
            ;

            data_properties =
                    properties                          [_val = qi::_1]
                >> *space
                >>  '|'
                >> *space
            ;

            caption_data %=
               *(
                    qi::char_ -
                    (linebreak >> qi::lit("|+")) -
                    (linebreak >> qi::lit("|-")) -
                    (linebreak >> qi::lit("|}")) -
                    (linebreak >> '|') -
                    (linebreak >> '!') -
                    (qi::lit("''") >> linebreak)
                )
            ;

            row_data %=
               *(
                    qi::char_ -
                    (linebreak >> qi::lit("|+")) -
                    (linebreak >> qi::lit("|-")) -
                    (linebreak >> '|') -
                    (linebreak >> '!') -
                    (linebreak >> qi::lit("|}"))
                )
            ;

            row_data_no_pp %=
                *(
                    qi::char_ -
                    (linebreak >> qi::lit("|+")) -
                    (linebreak >> qi::lit("|-")) -
                    (linebreak >> '|') -
                    (linebreak >> '!') -
                    (linebreak >> qi::lit("|}")) -
                    qi::lit("||")
                )
            ;

            row_data_no_pp_ee %=
                *(
                    qi::char_ -
                    (linebreak >> qi::lit("|+")) -
                    (linebreak >> qi::lit("|-")) -
                    (linebreak >> '|') -
                    (linebreak >> '!') -
                    (linebreak >> qi::lit("|}")) -
                    qi::lit("||") -
                    qi::lit("!!")
                )
            ;

            table_start =
                    qi::lit("{|")
                >  *space
                >  -(properties)
                >  *space
            ;

            table_end =
                    linebreak
                >   qi::lit("|}")
            ;

            table_caption =
                    linebreak
                >>  qi::lit("|+")
                >> *space
                >> -data_properties                             [at_c <1> (_val) = qi::_1]
                >>  qi::lit("''")
                >>  caption_data                                [at_c <0> (_val) = qi::_1]
                >>  qi::lit("''")
                >> *space
            ;

            table_header_cell =
                   *space
                >> -data_properties                             [at_c <1> (_val) = qi::_1]
                >   row_data_no_pp_ee                           [at_c <0> (_val) = qi::_1]
                >>  eps                                         [at_c <2> (_val) = true]
            ;

            table_cell =
                   *space
                >> -data_properties                             [at_c <1> (_val) = qi::_1]
                >   row_data_no_pp                              [at_c <0> (_val) = qi::_1]
                >>  eps                                         [at_c <2> (_val) = false]
            ;

            table_cells =
                linebreak >>
                (
                    (
                        just_pipe > table_cell                  [push_back(_val, qi::_1)]
                    )
                    |
                    (
                            qi::char_('!') > table_header_cell  [push_back(_val, qi::_1)]
                        >> *(qi::lit("!!") > table_header_cell  [push_back(_val, qi::_1)])
                    )
                )
                >> *(qi::lit("||") > table_cell                 [push_back(_val, qi::_1)])
            ;

            table_row =
                *(
                        table_cells                             [qi::_a = qi::_1]
                    >>  eps
                        [
                            phoenix::while_(!phoenix::empty(qi::_a))
                            [
                                phoenix::push_back(at_c <0> (_val), phoenix::front(qi::_a)),
                                phoenix::pop_front(qi::_a)
                            ]
                        ]
                )
            ;

            first_row %= table_row;

            table_rows =
                   -first_row                                           [phoenix::push_back(_val, qi::_1)]
                >> *(
                            linebreak
                        >>  qi::lit("|-")
                        >> *space
                        >> -properties                                  [at_c <1> (_a) = qi::_1]
                        >> *space
                        >>  table_row                                   [at_c <0> (_a) = at_c <0> (qi::_1)]
                    )                                                   [phoenix::push_back(_val, _a)]
            ;

            main =
                    eps             [_val = Table()]
                >>  table_start     [at_c <1> (_val) = qi::_1]
                >  -table_caption   [at_c <0> (_val) = qi::_1]
                >  -table_rows      [at_c <2> (_val) = qi::_1]
                >   table_end
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::map <std::string, std::string> > table_start;
        qi::rule <Iterator> table_end;
        qi::rule <Iterator, TableCaption()> table_caption;
        qi::rule <Iterator> just_pipe;
        qi::rule <Iterator, std::map <std::string, std::string> > data_properties;

        qi::rule <Iterator, std::string()> caption_data;
        qi::rule <Iterator, std::string()> row_data;
        qi::rule <Iterator, std::string()> row_data_no_pp;
        qi::rule <Iterator, std::string()> row_data_no_pp_ee;

        qi::rule <Iterator, TableCell()> table_cell;
        qi::rule <Iterator, TableCell()> table_header_cell;
        qi::rule <Iterator, std::deque <TableCell>()> table_cells;

        qi::rule <Iterator, TableRow(), qi::locals <std::deque <TableCell>>> table_row;
        qi::rule <Iterator, TableRow()> first_row;
        qi::rule <Iterator, std::vector <TableRow>(), qi::locals <TableRow>> table_rows;

        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        properties_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD properties;
    };

} // Parser
} // Components
} // WikiMarkup


#endif // COMPONENTS_PARSERS_TABLE_HPP_INCLUDED
