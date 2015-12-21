#ifndef COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED

#include "adaption.hpp"
#include "table_cell.hpp"

#include <vector>

namespace WikiMarkup { namespace Components { namespace Holders {

    struct TableRow
    {
        std::vector <TableCell> cells;
        std::map <std::string, std::string> attributes;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Holders::TableRow,
    (std::vector <WikiMarkup::Components::Holders::TableCell>, cells)
    (WikiMarkup::Components::Holders::strmap_type, attributes)
)

#endif // COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED
