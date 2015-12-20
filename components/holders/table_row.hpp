#ifndef COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED

#include "adaption.hpp"
#include "table_cell.hpp"

#include <vector>

namespace WikiMarkdown { namespace Components { namespace Holders {

    struct TableRow
    {
        std::vector <TableCell> cells;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkdown

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkdown::Components::Holders::TableRow,
    (std::vector <WikiMarkdown::Components::Holders::TableCell>, cells)
)

#endif // COMPONENTS_HOLDERS_TABLE_ROW_HPP_INCLUDED
