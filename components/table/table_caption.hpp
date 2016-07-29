#pragma once

#include "../../json_introspection.hpp"
#include "../adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components {

    struct TableCaption : public JSON::Stringifiable <TableCaption>
                        , public JSON::Parsable <TableCaption>
    {
        std::string data;
        std::map <std::string, std::string> attributes;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::TableCaption,
    (std::string, data)
    (WikiMarkup::Components::strmap_type, attributes)
)
