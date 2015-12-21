#ifndef COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED

#include "adaption.hpp"
#include "table_row.hpp"
#include "table_caption.hpp"

#include <string>
#include <map>
#include <vector>

namespace WikiMarkup { namespace Components { namespace Holders {

    struct Table
    {
        TableCaption caption;
        std::map <std::string, std::string> attributes;
        std::vector <TableRow> rows;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Holders::Table,
    (WikiMarkup::Components::Holders::TableCaption, caption)
    (WikiMarkup::Components::Holders::strmap_type, attributes)
    (std::vector <WikiMarkup::Components::Holders::TableRow>, rows)
)

#endif // COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
