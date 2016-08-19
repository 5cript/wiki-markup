#pragma once

#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableHeader : public IExportableComponent
                            , public JSON::Stringifiable <ExportableHeader>
                            , public JSON::Parsable <ExportableHeader>
    {
        std::string data;
        int level; // H1, H2, H3, ... = 1, 2, 3, ...

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableHeader,
    (std::string, data)
    (int, level)
)
