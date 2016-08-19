#pragma once

#include "exportable_components/exportable_text.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Text : public IComponent
                , public ExportableText
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        Text* clone() const override;
        std::string getRaw() const;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::Text, data)
