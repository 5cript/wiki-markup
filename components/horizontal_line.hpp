#ifndef HORIZONTAL_LINE_HPP_INCLUDED
#define HORIZONTAL_LINE_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "../json_introspection.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct HorizontalLine : public IComponent
                          , public JSON::Stringifiable <HorizontalLine>
                          , public JSON::Parsable <HorizontalLine>
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() override;
        void fromJson(std::string const& str) override;

        MetaInfo getMetaInfo() const override;
        HorizontalLine* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

/*
BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::HorizontalLine
)
*/

#endif // HORIZONTAL_LINE_HPP_INCLUDED
