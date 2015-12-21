#ifndef CONPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED
#define CONPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED

#include "adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkup { namespace Components { namespace Holders {

    struct TableCaption
    {
        std::string data;
        std::map <std::string, std::string> attributes;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Holders::TableCaption,
    (std::string, data)
    (WikiMarkup::Components::Holders::strmap_type, attributes)
)

#endif // CONPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED
