#ifndef PERIPHERALS_STYLE_NUMERICAL_VALUE_HPP_INCLUDED
#define PERIPHERALS_STYLE_NUMERICAL_VALUE_HPP_INCLUDED

#include "../value.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{
    struct Numerical : public Value
    {
        double value;

        Numerical() = default;
        Numerical(double value);
    };

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_NUMERICAL_VALUE_HPP_INCLUDED
