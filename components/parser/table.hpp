#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED

#include "../holders/table.hpp"
#include "../holders/table_cell.hpp"

#include "parser_core.hpp"
#include "properties.hpp"
#include "basic.hpp"

namespace WikiMarkdown { namespace Components { namespace Parser
{
    using namespace Holders;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct table_grammar : qi::grammar <Iterator, Table()>
    {
        using grammar_result = Table;

        // Parser
        table_grammar() : table_grammar::base_type(main, "table")
        {
            using namespace common_usings;
            using namespace Rules;
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
			main.name("table");

            table_start =
                    qi::lit("{|")
                >   *space
                >   -(properties)
                >   linebreak
            ;

            just_pipe =
                qi::char_('|')// - qi::lit("|+") - qi::lit("|-") - qi::lit("|}")
            ;

            table_header_cell =
                   *space
                >  -(
                            properties                          [at_c <1> (_val) = qi::_1]
                        >   '|'
                    )
                >  *(
                        qi::char_ -
                        linebreak -
                        qi::lit("!!") -
                        qi::lit("||")
                    )                                           [push_back(at_c <0> (_val), qi::_1)]
                >>  eps                                         [at_c <2> (_val) = true]
            ;

            table_cell =
                   *space
                >  -(
                            properties                          [at_c <1> (_val) = qi::_1]
                        >   qi::char_('|')
                    )
                >  *(qi::char_ - linebreak - qi::lit("||"))     [push_back(at_c <0> (_val), qi::_1)]
                >>  eps                                         [at_c <2> (_val) = false]
            ;

            table_cells =
                    just_pipe > table_cell
                /*
                (
                    (
                        just_pipe > table_cell             [push_back(_val, qi::_1)]
                    )
                    |
                    (
                            qi::char_('!') > table_header_cell  [push_back(_val, qi::_1)]
                        >  *(qi::lit("!!") > table_header_cell  [push_back(_val, qi::_1)])
                    )
                )
                >  *(qi::lit("||") > table_cell                 [push_back(_val, qi::_1)])
                */
                >   linebreak
            ;

            table_end =
                qi::lit("|}")
            ;

            table_caption =
                    qi::lit("|+")
                    // it is not required to put text.
                >   *(qi::char_ - linebreak)    [push_back(_val, qi::_1)]
                >   linebreak
            ;

            table_row =
                    table_cells                 [qi::_a = qi::_1]
                >>  eps
                    [
                        phoenix::while_(!phoenix::empty(qi::_a))
                        [
                            phoenix::push_back(at_c <0> (_val), phoenix::front(qi::_a)),
                            phoenix::pop_front(qi::_a)
                        ]
                    ]
            ;

            table_rows =
                   -(qi::lit("|-") > linebreak)
                >   table_row               [phoenix::push_back(_val, qi::_1)]
                >  *(
                            (qi::lit("|-") > linebreak)
                        >   table_row       [phoenix::push_back(_val, qi::_1)]
                    )
            ;

            main =
                    eps             [_val = Table()]
                >>  table_start     [at_c <1> (_val) = qi::_1]
                >  -table_caption   [at_c <0> (_val) = qi::_1]
                //>  -table_rows      [at_c <2> (_val) = qi::_1]
                >   table_cells
                >   table_end
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::map <std::string, std::string> > table_start;
        qi::rule <Iterator> table_end;
        qi::rule <Iterator, std::string()> table_caption;
        qi::rule <Iterator> just_pipe;

        qi::rule <Iterator, TableCell()> table_cell;
        qi::rule <Iterator, TableCell()> table_header_cell;
        qi::rule <Iterator, std::deque <TableCell>()> table_cells;

        qi::rule <Iterator, TableRow(), qi::locals <std::deque <TableCell>>> table_row;
        qi::rule <Iterator, std::vector <TableRow>()> table_rows;

        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        properties_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD properties;
    };

} // Parser
} // Components
} // WikiMarkdown


#endif // TABLE_HPP_INCLUDED
