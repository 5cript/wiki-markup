#pragma once

// JSON Includes
#include "../../json_value_ptr.hpp"
#include "SimpleJSON/utility/polymorphy.hpp"

#include "exportable_component.hpp"

#include "../list/list_type.hpp"

#include <string>
#include <vector>
#include <memory>

namespace WikiMarkup { namespace Components
{
    struct ListLine
    {
        std::string prefix;
        std::string data;
    };

    struct ListElement
    {
        virtual ~ListElement() = default;
        virtual ListElement* clone() const = 0;
    };

    struct ListTextLine : public ListElement
                        , public JSON::Stringifiable <ListTextLine>
                        , public JSON::Parsable <ListTextLine>
    {
        std::string data;

        ListTextLine(std::string const& data = "");

        ListTextLine* clone() const override;
    };

    struct PrimalList : public ListElement
                      , public JSON::Stringifiable <PrimalList>
                      , public JSON::Parsable <PrimalList>
    {
        ListType type;
        std::vector <sutil::value_ptr <ListElement>> elements;

        PrimalList* clone() const override;
    };

    struct ExportableList : public IExportableComponent
                          , public JSON::Stringifiable <ExportableList>
                          , public JSON::Parsable <ExportableList>
    {
        PrimalList list;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListLine,
    (std::string, prefix)
    (std::string, data)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableList,
    (WikiMarkup::Components::PrimalList, list)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::PrimalList,
    (WikiMarkup::Components::ListType, type)
    (std::vector <sutil::value_ptr <WikiMarkup::Components::ListElement>>, elements)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListTextLine,
    (std::string, data)
)

JSON_DECLARE_POLYMORPHIC(WikiMarkup::Components::ListElement, (WikiMarkup::Components::ListTextLine)(WikiMarkup::Components::PrimalList))
