#ifndef COMPONENTS_LIST_HPP_INCLUDED
#define COMPONENTS_LIST_HPP_INCLUDED

#include "../SimpleUtil/value_ptr/value_ptr.hpp"

#include "list/list_type.hpp"

#include "component.hpp"
#include "adaption.hpp"

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
    {
        std::string data;

        ListTextLine(std::string const& data);

        ListElement* clone() const override;
    };

    struct List : public IComponent, public ListElement
    {
        ListType type;
        std::vector <sutil::value_ptr <ListElement>> elements;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        std::string getName() const override;

        ListElement* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ListLine,
    (std::string, prefix)
    (std::string, data)
)

#endif // COMPONENTS_LIST_HPP_INCLUDED
