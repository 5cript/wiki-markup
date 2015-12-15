#ifndef COMPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED

#include "adaption.hpp"

#include <string>
#include <map>

namespace WikiMarkdown { namespace Components { namespace Holders {

    struct TableCaptionData
    {
        std::string caption;
        std::map <std::string, std::string> attributes;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkdown

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkdown::Components::Holders::TableCaptionData,
    (std::string, caption)
    (WikiMarkdown::Components::Holders::strmap_type, attributes)
)


#endif // COMPONENTS_HOLDERS_TABLE_CAPTION_HPP_INCLUDED
