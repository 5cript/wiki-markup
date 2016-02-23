#ifndef COMPONENTS_PARSERS_URI_IPV6_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_IPV6_HPP_INCLUDED

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

#include "ipv4.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <iomanip>
#include <sstream>

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    namespace Internal
    {
        inline std::string vecStrAccumulator(std::vector <std::string> const& vec) {
            std::string res;
            for (auto const& i : vec)
                res += i;
            return res;
        }
    }

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct ipv6s_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        ipv6s_grammar() : ipv6s_grammar::base_type(main, "ipv6s")
        {
            using namespace common_usings;
            INSTALL_DEBUG_HANDLER;

			using std::array;

            h16 = repeat(1, 4)[qi::xdigit] - ipv4s;

            ls32 =
                (
                        ipv4s   [_val = qi::_1]
                    |   (h16 >> qi::char_(':') >> h16)  [_val = qi::_1]
                )
            ;

            h16_colon =
                h16 >> qi::char_(':')
            ;

            colon_h16 =
                qi::char_(':') >> h16
            ;

            /*
            ipv6 =
                                                                                      repeat(6)[h16 >> qi::char_(':')] >> ls32
                |                                                    qi::lit("::") >> repeat(5)[h16 >> qi::char_(':')] >> ls32
                |   -(                                       h16) >> qi::lit("::") >> repeat(4)[h16 >> qi::char_(':')] >> ls32
                |   -(repeat(0, 1)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::") >> repeat(3)[h16 >> qi::char_(':')] >> ls32
                |   -(repeat(0, 2)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::") >> repeat(2)[h16 >> qi::char_(':')] >> ls32
                |   -(repeat(0, 3)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::") >>           h16 >> qi::char_(':')  >> ls32
                |   -(repeat(0, 4)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::")                                     >> ls32
                |   -(repeat(0, 5)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::") >>           h16
                |   -(repeat(0, 6)[h16 >> qi::char_(':')] >> h16) >> qi::lit("::")
            ;
            */

            beforeAbreviation =
                    repeat(_r1) [h16_colon]
                    [
                        _val += phoenix::bind(&Internal::vecStrAccumulator, phoenix::cref(qi::_1))
                    ]
                >>  h16                             [_val += qi::_1]
            ;

            afterAbreviation =
                (
                        repeat(0, _r1)
                        [
                            h16_colon       [_val += qi::_1]
                        ]
                    >>  (
                                ls32        [_val += qi::_1]
                            |   h16         [_val += qi::_1]
                        )
                )
                |
                (
                    h16                     [_val += qi::_1]
                )
            ;

            abreviation =
                    lit("::")               [_val = "::"]
                >> -afterAbreviation(_r1)   [_val += qi::_1]
            ;

            ipv6 =
                (
                    (
                        beforeAbreviation(7)            [_a = qi::_1]
                    )
                |   (
                            beforeAbreviation(6)            [_a = qi::_1]
                        >>  lit("::")                       [_a += "::"]
                    )
                |   (
                            beforeAbreviation(5)            [_a = qi::_1]
                        >>  lit("::")                       [_a += "::"]
                        >> -h16                             [_a += qi::_1]
                    )
                |   (
                            beforeAbreviation(4)            [_a = qi::_1]
                        >>  abreviation(0)                  [_a += qi::_1]
                    )
                |   (
                            beforeAbreviation(3)            [_a = qi::_1]
                        >>  abreviation(1)                  [_a += qi::_1]
                    )
                |   (
                            beforeAbreviation(2)            [_a = qi::_1]
                        >>  abreviation(2)                  [_a += qi::_1]
                    )
                |   (
                            beforeAbreviation(1)            [_a = qi::_1]
                        >>  abreviation(3)                  [_a += qi::_1]
                    )
                |   (
                            beforeAbreviation(0)            [_a = qi::_1]
                        >>  abreviation(4)                  [_a += qi::_1]
                    )
                |   (
                        abreviation(5)                      [_a = qi::_1]
                    )
                )
                >> eps [_val = _a]
            ;

            main =
                ipv6
            ;
        }

        // Rules
        qi::rule <Iterator, std::string()> ls32; // see RFC
        qi::rule <Iterator, std::string()> h16; // h16 = 2 byte hex => see RFC
        qi::rule <Iterator, std::string()> h16_colon;
        qi::rule <Iterator, std::string()> colon_h16;

        qi::rule <Iterator, std::string(int)> beforeAbreviation;
        qi::rule <Iterator, std::string(int)> abreviation;
        qi::rule <Iterator, std::string(int)> afterAbreviation;

        qi::rule <Iterator, std::string(), qi::locals <std::string> > ipv6;

        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        ipv4s_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD ipv4s;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_IPV6_HPP_INCLUDED
