#ifndef PERIPHERALS_PARSERS_STYLE_URL_HPP_INCLUDED
#define PERIPHERALS_PARSERS_STYLE_URL_HPP_INCLUDED

#include "../../../parser/qi_common/parser_core.hpp"
#include "../../../parser/qi_common/basic.hpp"

#include "../../style/value_types/url.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace Parser
{

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct url_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        url_grammar() : url_grammar::base_type(main, "url")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			no_close_paren %= qi::char_ - qi::char_(')');

			no_quote %= qi::char_ - qi::char_('"');

			main =
                    qi::lit("url(")
                >> *space
                >>  ((
                            qi::char_('"')
                        >> *no_quote            [_val = qi::_1]
                        >>  qi::char_('"')
                    )
                    |
                    (
                            no_close_paren
                    ))
                >> *space
                >>  qi::char_(')')
			;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, std::string()> no_close_paren;
        qi::rule <Iterator, std::string()> no_quote;
    };

} // namespace Parser
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_PARSERS_STYLE_URL_HPP_INCLUDED
