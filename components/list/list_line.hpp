#pragma once

#include "../../json_introspection.hpp"

namespace WikiMarkup { namespace Components
{
    struct ListLine : public JSON::Stringifiable <ListLine>
                    , public JSON::Parsable <ListLine>
    {
        std::string prefix;
        std::string data;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListLine,
    (std::string, prefix)
    (std::string, data)
)
