#ifndef COMPONENTS_LIST_HPP_INCLUDED
#define COMPONENTS_LIST_HPP_INCLUDED

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
    };

    struct ListTextLine : public ListElement
    {
        std::string data;

        ListTextLine(std::string const& data);
    };

    struct List : public IComponent, public ListElement
    {
        ListType type;
        std::vector <std::unique_ptr <ListElement>> elements;

        std::string toMarkup() override;
        void fromMarkup(std::string const& mu) override;
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
