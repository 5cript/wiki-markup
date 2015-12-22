#ifndef COMPONENTS_LIST_HPP_INCLUDED
#define COMPONENTS_LIST_HPP_INCLUDED

#include "list/list_type.hpp"

#include "component.hpp"
#include "adaption.hpp"

#include <string>
#include <vector>
#include <boost/variant/recursive_variant.hpp>

namespace WikiMarkup { namespace Components {

    struct List;

    // using a dirty hack to get the recursive struct.
    // is not actually an array, but more like a boost::optional,
    // which is not suitable for
    using ListNode = std::vector <
        List
    >;

    // this format is well parsable, but not useful for actual use
    struct List : public IComponent
    {
        ListNode child;
        ListNode subList;

        ListType type;
        std::string data;

        std::string toMarkup() override;
        void fromMarkup(std::string const& mu) override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::List,
    (WikiMarkup::Components::ListNode, child)
    (WikiMarkup::Components::ListNode, subList)
    (WikiMarkup::Components::ListType, type)
    (std::string, data)
)

#endif // COMPONENTS_LIST_HPP_INCLUDED
