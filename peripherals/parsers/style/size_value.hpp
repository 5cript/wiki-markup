#ifndef PERIPHERALS_PARSERS_STYLE_SIZE_VALUE_HPP_INCLUDED
#define PERIPHERALS_PARSERS_STYLE_SIZE_VALUE_HPP_INCLUDED

#include "../../size_value.hpp"
#include "../../../parser/parser_core.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace Parser
{

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct size_value_grammar : qi::grammar <Iterator, SizeValue>
    {
        using grammar_result = SizeValue;

        size_value_grammar() : size_value_grammar::base_type(main, "size_value")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			unit.add
                ("em", SizeUnit::em)
                ("ex", SizeUnit::ex)
                ("%", SizeUnit::percent)
                ("px", SizeUnit::px)
                ("cm", SizeUnit::cm)
                ("mm", SizeUnit::mm)
                ("in", SizeUnit::in)
                ("pt", SizeUnit::pt)
                ("pc", SizeUnit::pc)
                ("ch", SizeUnit::ch)
                ("rem", SizeUnit::rem)
                ("vh", SizeUnit::vh)
                ("vw", SizeUnit::vw)
                ("vmin", SizeUnit::vmin)
                ("vmax", SizeUnit::vamx)
			;

            main =
                    double_
                >>  qi::no_case
                    [
                        unit
                    ]
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Symbols
        qi::symbols <char const, SizeUnit> unit;
    };

} // namespace Parser
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_PARSERS_STYLE_SIZE_VALUE_HPP_INCLUDED
