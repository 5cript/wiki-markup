#pragma once

#include "exportable_component.hpp"
#include "../url.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableLink : public IExportableComponent
                          , public JSON::Stringifiable <ExportableLink>
                          , public JSON::Parsable <ExportableLink>
    {
        bool internal;
        bool implicit;
        bool colon; // contains colon :
        bool anchor; // contains #

        std::string prefix;
        std::string localPart;
        std::vector <std::string> attributes;

        Url url;

        bool redirect;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableLink,
    (bool,                          internal)   // 0
    (bool,                          implicit)   // 1
    (bool,                          colon)      // 2
    (bool,                          anchor)     // 3
    (std::string,                   prefix)     // 4
    (std::string,                   localPart)  // 5
    (std::vector <std::string>,     attributes) // 6
    (WikiMarkup::Components::Url,   url)        // 7
    (bool,                          redirect)   // 8
)
