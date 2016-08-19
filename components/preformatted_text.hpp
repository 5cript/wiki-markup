#pragma once

#include "exportable_components/exportable_preformatted_text.hpp"
#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include <string>
#include <vector>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct PreformattedText : public IComponent
                            , public ExportablePreformattedText
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        PreformattedText* clone() const override;
        std::string getRaw() const;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::PreformattedText, lines
)
