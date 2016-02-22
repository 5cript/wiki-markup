#ifndef PERIPHERALS_STYLE_STYLE_ATTRIBUTE_HPP_INCLUDED
#define PERIPHERALS_STYLE_STYLE_ATTRIBUTE_HPP_INCLUDED

#include "../adaption.hpp"

#include "value.hpp"

#include <string>
#include <vector>
#include <memory>

namespace WikiMarkup { namespace Peripherals  { namespace Style
{
    // This type is solely for parsing.
    struct RawAttribute
    {
        std::string key;
        std::vector <std::string> values;
    };

    // This type is for use, after parsing and preprocessing.
    struct Attribute
    {
        std::string key;
        std::vector <std::unique_ptr <Value> > values;
    };

} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Peripherals::Style::RawAttribute,
    key, values
)

#endif // PERIPHERALS_STYLE_STYLE_ATTRIBUTE_HPP_INCLUDED
