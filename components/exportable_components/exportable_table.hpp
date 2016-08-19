#pragma once

#include "exportable_component.hpp"

#include "../table/table_row.hpp"
#include "../table/table_caption.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableTable : public IExportableComponent
                           , public JSON::Stringifiable <ExportableTable>
                           , public JSON::Parsable <ExportableTable>
    {
        TableCaption caption;
        std::map <std::string, std::string> attributes;
        std::vector <TableRow> rows;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableTable,
    (WikiMarkup::Components::TableCaption, caption)
    (WikiMarkup::Components::strmap_type, attributes)
    (std::vector <WikiMarkup::Components::TableRow>, rows)
)
