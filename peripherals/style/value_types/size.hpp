#ifndef PERIPHERALS_STYLE_SIZE_VALUE_HPP_INCLUDED
#define PERIPHERALS_STYLE_SIZE_VALUE_HPP_INCLUDED

#include "../value.hpp"

#include <string>
#include <cstdint>

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{
    // Source: http://www.w3schools.com/cssref/css_units.asp
    // WARNING: MODIFY SOURCE IF YOU DO CHANGES TO THIS! AND PARSER
    enum class SizeUnit
    {
        em, ex, percent, px, cm, mm, in, pt, pc,
        ch,
        rem,
        vh, vw,
        vmin,
        vmax
    };

    /**
     *  Holds values like 10px, 2em, 12.5%
     */
    struct SizeValue : public Value
    {
        SizeUnit unit;
        double value;
    };

    /**
     *  Converts a string into an enum value.
     *
     *  @param unit A unit as a string, such as "px".
     *  @return Returns a unit as the enum value.
     */
    SizeUnit getUnitFromString(std::string const& unit);

    /**
     *  Converts a unit enum value into a string.
     *
     *  @param unit A unit as an enum value, such as "px".
     *  @return Returns a unit as a string.
     */
    std::string unitToString(SizeUnit unit);

} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_SIZE_VALUE_HPP_INCLUDED
