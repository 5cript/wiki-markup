#ifndef PERIPHERALS_STYLE_URL_VALUE_HPP_INCLUDED
#define PERIPHERALS_STYLE_URL_VALUE_HPP_INCLUDED

#include "../value.hpp"

#include <boost/optional.hpp>

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{
    struct Url : public Value
    {
        std::string value;

        Url() = default;
        Url(std::string value);
    };

    boost::optional <Url> tryGetUrlFromString(std::string const& str);

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_URL_VALUE_HPP_INCLUDED
