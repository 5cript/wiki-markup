#ifndef PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED
#define PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED

#include "../adaption.hpp"

#include "value.hpp"

namespace WikiMarkup { namespace Peripherals  { namespace Style {
{
    struct StringValue : public Value
    {
        std::string value;
    };
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Peripherals::Style::StringValue,
    value
)

#endif // PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED
