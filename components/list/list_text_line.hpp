#pragma once

#include "../../json_introspection.hpp"
#include "list_element.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    struct ListTextLine : public ListElement
                        , public JSON::Stringifiable <ListTextLine>
                        , public JSON::Parsable <ListTextLine>
    {
        std::string data;

        ListTextLine(std::string const& data = "");

        ListTextLine* clone() const override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListTextLine,
    (std::string, data)
)
