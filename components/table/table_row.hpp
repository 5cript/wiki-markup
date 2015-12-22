#ifndef COMPONENTS_TABLE_ROW_HPP_INCLUDED
#define COMPONENTS_TABLE_ROW_HPP_INCLUDED

#include "../adaption.hpp"
#include "table_cell.hpp"

#include <vector>

namespace WikiMarkup { namespace Components {

    struct TableRow
    {
        std::vector <TableCell> cells;
        std::map <std::string, std::string> attributes;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::TableRow,
    (std::vector <WikiMarkup::Components::TableCell>, cells)
    (WikiMarkup::Components::strmap_type, attributes)
)

#endif // COMPONENTS_TABLE_ROW_HPP_INCLUDED
