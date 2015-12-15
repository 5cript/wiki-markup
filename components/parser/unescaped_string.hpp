#ifndef UNESCAPED_STRING_HPP_INCLUDED
#define UNESCAPED_STRING_HPP_INCLUDED

#include "parser_core.hpp"

namespace WikiMarkdown { namespace Components { namespace Parser
{

    namespace Internal
    {
        void removeQuotes(std::string& str) {
            if (str.length() <= 2)
                return;
            str = str.substr(1, str.length() - 2);
        }
    }

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct unescaped_string_grammar : qi::grammar<Iterator, std::string()>
    {
        unescaped_string_grammar() : unescaped_string_grammar::base_type(main)
        {
            using namespace common_usings;

            unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                          ("\\r", '\r')("\\t", '\t')("\\v", '\v')
                          ("\\\\", '\\')("\\\'", '\'')("\\\"", '\"')
            ;

            unesc_str =
                    qi::lit("\"")
                >> *(unesc_char | qi::alnum | "\\x" >> qi::hex)
                >>  qi::lit("\"")
            ;

            main =
                    unesc_str       [_val = qi::_1]
                >>  eps             [phoenix::bind(&Internal::removeQuotes, phoenix::ref(_val))]
            ;
        }

        qi::rule<Iterator, std::string()> unesc_str;
        qi::rule<Iterator, std::string()> main;
        qi::symbols<char const, char const> unesc_char;
    };
} // Parser
} // Components
} // WikiMarkdown

#endif // UNESCAPED_STRING_HPP_INCLUDED
