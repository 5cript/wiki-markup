#pragma once

#include "exportable_components/exportable_table.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include <string>
#include <map>
#include <vector>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Table : public IComponent
                 , public ExportableTable
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        Table* clone() const override;
    };

    Table stripHeaders(Table const& table);
    std::vector <TableCell> getHorizontalHeaders(Table const& table);
    std::vector <TableCell> getVerticalHeaders(Table const& table, bool noOverlap = true);

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Table,
    (WikiMarkup::Components::TableCaption, caption)
    (WikiMarkup::Components::strmap_type, attributes)
    (std::vector <WikiMarkup::Components::TableRow>, rows)
)
