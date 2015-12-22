#ifndef COMPONENTS_TABLE_CAPTION_HPP_INCLUDED
#define COMPONENTS_TABLE_CAPTION_HPP_INCLUDED

#include "../adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components {

    struct TableCaption
    {
        std::string data;
        std::map <std::string, std::string> attributes;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::TableCaption,
    (std::string, data)
    (WikiMarkup::Components::strmap_type, attributes)
)

#endif // COMPONENTS_TABLE_CAPTION_HPP_INCLUDED
