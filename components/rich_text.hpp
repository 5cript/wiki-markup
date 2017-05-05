#pragma once

#include "exportable_components/exportable_rich_text.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct RichText : public IComponent
                    , public ExportableRichText
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        RichText* clone() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::RichText, subelements)
