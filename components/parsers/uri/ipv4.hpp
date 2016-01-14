#ifndef COMPONENTS_PARSERS_URI_IPV4_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_IPV4_HPP_INCLUDED

#include "../parser_core.hpp"
#include "../basic.hpp"

#include <cstdint>
#include <string>
#include <sstream>

namespace WikiMarkup { namespace Components { namespace Parser
{
    namespace Internal
    {
        std::string intToStr(uint8_t v) {
            std::stringstream sstr;
            sstr << (int)v;
            return sstr.str();
        }
    }

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct ipv4s_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        ipv4s_grammar() : ipv4s_grammar::base_type(main, "ipv4s")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;
			INSTALL_DEBUG_HANDLER;

            section =
                    boost::spirit::qi::uint_parser<uint8_t, 10, 1, 3>() [_a = qi::_1]
                >>  eps [_val = phoenix::bind(&Internal::intToStr, _a)]
            ;

            main =
                    section             [_val += qi::_1]
                >>  qi::char_('.')      [phoenix::push_back(_val, qi::_1)]
                >>  section             [_val += qi::_1]
                >>  qi::char_('.')      [phoenix::push_back(_val, qi::_1)]
                >>  section             [_val += qi::_1]
                >>  qi::char_('.')      [phoenix::push_back(_val, qi::_1)]
                >>  section             [_val += qi::_1]
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string(), qi::locals <uint8_t> > section;

        qi::rule <Iterator, grammar_result()> main;
    };

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct ipv4_grammar : qi::grammar <Iterator, uint32_t()>
    {
        using grammar_result = uint32_t;

        ipv4_grammar() : ipv4_grammar::base_type(main, "ipv4")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			section = boost::spirit::qi::uint_parser<std::uint8_t, 10, 1, 3>();

            main =
                    eps             [_val = 0]
                >>  section         [_val |= (qi::_1 << 24)] >> '.'
                >>  section         [_val |= (qi::_1 << 16)] >> '.'
                >>  section         [_val |= (qi::_1 << 8) ] >> '.'
                >>  section
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::uint8_t()> section;

        qi::rule <Iterator, grammar_result()> main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_IPV4_HPP_INCLUDED
