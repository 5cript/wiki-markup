#ifndef COMPONENTS_PARSERS_URI_DOMAIN_NAME_HPP_INCLUDED
#define COMPONENTS_PARSERS_URI_DOMAIN_NAME_HPP_INCLUDED

#include "../parser_core.hpp"
#include "../basic.hpp"

#include <string>
#include <vector>

namespace WikiMarkup { namespace Components { namespace Parser
{
    namespace Internal
    {
        std::string dotConcatStrings(std::vector <std::string> const& strings) {
            if (strings.empty())
                return "";

            std::string result;
            for (auto iter = std::begin(strings); iter < std::end(strings) - 1; ++iter) {
                result += *iter;
                result.push_back('.');
            }
            result += strings.back();
            return result;
        }
    }

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct domain_name_grammar : qi::grammar <Iterator, std::string(), qi::locals <std::vector <std::string>>>
    {
        using grammar_result = std::string;

        domain_name_grammar() : domain_name_grammar::base_type(main, "domain_name")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			section =
                    qi::alnum                           [phoenix::push_back(_val, qi::_1)]
                >> *(
                            qi::alnum                   [phoenix::push_back(_val, qi::_1)]
                        |   (
                                    qi::char_('-')      [phoenix::push_back(_val, qi::_1)]
                                >>  qi::alnum           [phoenix::push_back(_val, qi::_1)]
                            )
                    )
			;

			sections =
                section % '.'
            ;

            main =
                    sections    [_a = qi::_1]
                >>  eps
                    [
                        _val = phoenix::bind(&Internal::dotConcatStrings, phoenix::cref(_a))
                    ]
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> section;
        qi::rule <Iterator, std::vector <std::string>()> sections;
        qi::rule <Iterator, grammar_result(), qi::locals <std::vector <std::string>>> main;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_URI_DOMAIN_NAME_HPP_INCLUDED
