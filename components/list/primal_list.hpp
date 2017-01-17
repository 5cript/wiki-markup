#pragma once

#include "list_element.hpp"
#include "list_type.hpp"

#include "../../json_introspection.hpp"
#include "../../json_value_ptr.hpp"

#include <vector>

namespace WikiMarkup { namespace Components
{
    struct PrimalList : public ListElement
                      , public JSON::Stringifiable <PrimalList>
                      , public JSON::Parsable <PrimalList>
    {
        ListType type;
        std::vector <sutil::value_ptr <ListElement>> elements;

        PrimalList* clone() const override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::PrimalList,
    (WikiMarkup::Components::ListType, type)
    (std::vector <sutil::value_ptr <WikiMarkup::Components::ListElement>>, elements)
)

