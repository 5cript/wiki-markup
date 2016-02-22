#ifndef PERIPHERALS_STYLE_COLOR_HPP_INCLUDED
#define PERIPHERALS_STYLE_COLOR_HPP_INCLUDED

#include "../adaption.hpp"

#include "value.hpp"

#include <cstdint>

namespace WikiMarkup { namespace Peripherals  { namespace Style {
{
    /**
     *  RGBA color. 24bit + alpha.
     */
    struct Color : public Value
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    };
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Peripherals::Style::Color,
    R, G, B, A
)

#endif // PERIPHERALS_STYLE_COLOR_HPP_INCLUDED
