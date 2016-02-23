#ifndef COMPONENTS_TABLE_HPP_INCLUDED
#define COMPONENTS_TABLE_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "table/table_row.hpp"
#include "table/table_caption.hpp"

#include <string>
#include <map>
#include <vector>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Table : public IComponent
    {
        TableCaption caption;
        std::map <std::string, std::string> attributes;
        std::vector <TableRow> rows;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        MetaInfo getMetaInfo() const override;
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

#endif // COMPONENTS_TABLE_HPP_INCLUDED
