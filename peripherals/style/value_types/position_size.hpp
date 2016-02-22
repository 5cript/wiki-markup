#ifndef PERIPHERALS_STYLE_POSITION_SIZE_HPP_INCLUDED
#define PERIPHERALS_STYLE_POSITION_SIZE_HPP_INCLUDED

#include "../value.hpp"
#include "size.hpp"

namespace WikiMarkup { namespace Peripherals  { namespace Style { namespace ValueTypes
{

    struct PositionAndSize
    {
        SizeValue left;
        SizeValue top;
        SizeValue width;
        SizeValue height;
    };

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_POSITION_SIZE_HPP_INCLUDED
