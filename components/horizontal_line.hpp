#pragma once

#include "exportable_components/exportable_horizontal_line.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct HorizontalLine : public IComponent
                          , public ExportableHorizontalLine
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        HorizontalLine* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::HorizontalLine
)
