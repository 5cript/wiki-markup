#pragma once

#include "../adaption.hpp"
#include "../../json_introspection.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components {

    struct TableCell : public JSON::Stringifiable <TableCell>
                     , public JSON::Parsable <TableCell>
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
