#ifndef PERIPHERALS_STYLE_COLOR_HPP_INCLUDED
#define PERIPHERALS_STYLE_COLOR_HPP_INCLUDED

#include "../../adaption.hpp"

#include "../value.hpp"

#include <string>
#include <cstdint>
#include <boost/optional.hpp>

namespace WikiMarkup { namespace Peripherals { namespace Style
{
    // This is an intermediate, not intended for external use
    struct HslColor
    {
        uint16_t h;
        double s;
        double l;
        double a;
    };

    /**
     *  RGBA color. 24bit + alpha.
     */
    struct Color : public Value
    {
        std::string originalString;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        double a;

        Color(uint8_t r, uint8_t g, uint8_t b, double a);
        Color() = default;
    };

    Color colorFromString(std::string const& color);
    boost::optional <Color> tryGetColorFromString(std::string const& color);
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Peripherals::Style::HslColor,
    h, s, l, a
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Peripherals::Style::Color,
    r, g, b, a
)

#endif // PERIPHERALS_STYLE_COLOR_HPP_INCLUDED
