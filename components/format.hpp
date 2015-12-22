#ifndef COMPONENTS_FORMAT_HPP_INCLUDED
#define COMPONENTS_FORMAT_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct FormattedString
    {
        std::string data;
        bool fat;
        bool italic;
        bool striked;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::FormattedString,
    (std::string, data)
    (bool, fat)
    (bool, italic)
    (bool, striked)
)


#endif // COMPONENTS_FORMAT_HPP_INCLUDED
