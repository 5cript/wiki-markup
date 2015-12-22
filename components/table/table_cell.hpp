#ifndef COMPONENTS_TABLE_CELL_HPP_INCLUDED
#define COMPONENTS_TABLE_CELL_HPP_INCLUDED

#include "../adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components {

    struct TableCell
    {
        std::string data;
        std::map <std::string, std::string> attributes;
        bool isHeaderCell; // faster than polymorphy
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::TableCell,
    (std::string, data)
    (WikiMarkup::Components::strmap_type, attributes)
    (bool, isHeaderCell)
)

#endif // COMPONENTS_TABLE_CELL_HPP_INCLUDED
