#ifndef COMPONENTS_HEADER_HPP_INCLUDED
#define COMPONENTS_HEADER_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct Header : public IComponent
    {
        std::string text;
        int level; // H1, H2, H3, ... = 1, 2, 3, ...
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Header,
    (std::string, text)
    (int, level)
)

#endif // COMPONENTS_HEADER_HPP_INCLUDED
