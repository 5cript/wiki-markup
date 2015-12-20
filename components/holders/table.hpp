#ifndef COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED

#include "adaption.hpp"
#include "table_row.hpp"

#include <string>
#include <map>
#include <vector>

namespace WikiMarkdown { namespace Components { namespace Holders {

    struct Table
    {
        std::string caption;
        std::map <std::string, std::string> attributes;
        std::vector <TableRow> rows;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkdown

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkdown::Components::Holders::Table,
    (std::string, caption)
    (WikiMarkdown::Components::Holders::strmap_type, attributes)
    (std::vector <WikiMarkdown::Components::Holders::TableRow>, rows)
)

#endif // COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
