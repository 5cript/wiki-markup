#ifndef COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED

#include "adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components { namespace Holders {

    struct TableCell
    {
        std::string data;
        std::map <std::string, std::string> attributes;
        bool isHeaderCell; // faster than polymorphy
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Holders::TableCell,
    (std::string, data)
    (WikiMarkup::Components::Holders::strmap_type, attributes)
    (bool, isHeaderCell)
)

#endif // COMPONENTS_HOLDERS_TABLE_CELL_HPP_INCLUDED
