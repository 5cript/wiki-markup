#ifndef COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED

#include "adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkdown { namespace Components { namespace Holders {

    struct TableCell
    {
        std::string data;
        std::map <std::string, std::string> attributes;
        bool isHeaderCell; // faster than polymorphy
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkdown

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkdown::Components::Holders::TableCell,
    (std::string, data)
    (WikiMarkdown::Components::Holders::strmap_type, attributes)
    (bool, isHeaderCell)
)

#endif // COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED
