#ifndef PERIPHERALS_STYLE_KEYWORD_HPP_INCLUDED
#define PERIPHERALS_STYLE_KEYWORD_HPP_INCLUDED

#include "mplex/string/string.hpp"

#include <cstring>

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{
    template <typename T, typename... List>
    struct ValidKeywords
    {
        /**
         *  Returns the keyword or an empty string
         */
        static constexpr bool isKeyword(std::string const& rhs)
        {
            return rhs == std::string(T::c_str) ? true : ValidKeywords <List...>::isKeyword(rhs);
        }
    };

    template <typename T>
    struct ValidKeywords <T>
    {
        static constexpr bool isKeyword(std::string const& rhs)
        {
            return std::string(T::c_str) == rhs;
        }
    };

    template <typename... Keywords>
    struct Keyword : public Value
    {
        using keywords = ValidKeywords <Keywords...>;

        std::string value;

        bool verify() const
        {
            return keywords::isKeyword(value);
        }
    };

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

/*
 *  ANY_KEYWORD <SHORT_STRING("initial"),
                 SHORT_STRING("inherit"),
                 SHORT_STRING("or_else")>
 *
 *
 *
 *
 */


#endif // PERIPHERALS_STYLE_KEYWORD_HPP_INCLUDED
