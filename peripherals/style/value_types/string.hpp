#ifndef PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED
#define PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED

#include "../value.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{

    struct StringValue : public Value
    {
        std::string value;
    };

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_STRING_VALUE_HPP_INCLUDED
