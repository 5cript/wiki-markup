#ifndef COMPONENTS_LIST_HPP_INCLUDED
#define COMPONENTS_LIST_HPP_INCLUDED

#include "SimpleUtil/value_ptr/value_ptr.hpp"

#include "list/list_type.hpp"

#include "component.hpp"
#include "adaption.hpp"

#include "../json_introspection.hpp"
#include "../json_value_ptr.hpp"
#include "SimpleJSON/utility/polymorphy.hpp"

#include <string>
#include <vector>
#include <memory>

namespace WikiMarkup { namespace Components {

    struct ListLine
    {
        std::string prefix;
        std::string data;
    };

    // this format is well parsable, but not useful for actual use
    using PlainList = std::vector <ListLine>;

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

    struct List : public IComponent
                , public JSON::Stringifiable <List>
                , public JSON::Parsable <List>
    {
        PrimalList list;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;

        MetaInfo getMetaInfo() const override;
        List* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListLine,
    (std::string, prefix)
    (std::string, data)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::List,
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

#endif // COMPONENTS_LIST_HPP_INCLUDED
