#pragma once

#include "exportable_components/exportable_header.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "../json_introspection.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Header : public IComponent
                  , public ExportableHeader
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        Header* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Header,
    (std::string, data)
    (int, level)
)
