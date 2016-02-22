#ifndef PERIPHERALS_STYLE_RECT_HPP_INCLUDED
#define PERIPHERALS_STYLE_RECT_HPP_INCLUDED

#include "../value.hpp"
#include "size.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{

    struct Rect
    {
        SizeValue left;
        SizeValue top;
    };

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_RECT_HPP_INCLUDED
