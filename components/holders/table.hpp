#ifndef COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
#define COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED

#include "table_caption.hpp"

#include <string>
#include <string>

namespace WikiMarkdown { namespace Components { namespace Holders {

    struct TableData
    {
        TableCaptionData caption;
        std::map <std::string, std::string> attributes;
    };

} // namespace Holders
} // namespace Components
} // namespace WikiMarkdown

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkdown::Components::Holders::TableData,
    (WikiMarkdown::Components::Holders::TableCaptionData, caption)
    (WikiMarkdown::Components::Holders::strmap_type, attributes)
)

#endif // COMPONENTS_HOLDERS_TABLE_HPP_INCLUDED
