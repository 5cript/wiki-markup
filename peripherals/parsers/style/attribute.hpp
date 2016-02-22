#ifndef ATTRIBUTE_HPP_INCLUDED
#define ATTRIBUTE_HPP_INCLUDED

#include "../../style/attribute_definition.hpp"
#include "../../style/attribute.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace Parser
{

    Attribute parseAttribute(RawAttribute const& rawAttribute);

} // namespace Parser
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // ATTRIBUTE_HPP_INCLUDED
