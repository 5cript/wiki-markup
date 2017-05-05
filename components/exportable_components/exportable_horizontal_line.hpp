#pragma once

#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableHorizontalLine : public virtual IExportableComponent
                                    , public JSON::Stringifiable <ExportableHorizontalLine>
                                    , public JSON::Parsable <ExportableHorizontalLine>
    {
        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableHorizontalLine* clone() const override;

        static MetaInfo getMetaInfoS() { return {"HorizontalLine", true}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableHorizontalLine,
)
