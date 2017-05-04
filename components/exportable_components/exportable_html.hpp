#pragma once

#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableHtml : public IExportableComponent
                          , public JSON::Stringifiable <ExportableHtml>
                          , public JSON::Parsable <ExportableHtml>
    {
        std::string data;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableHtml* clone() const override;

        static MetaInfo getMetaInfoS() { return {"Html", false}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableHtml,
    (std::string, data)
)
