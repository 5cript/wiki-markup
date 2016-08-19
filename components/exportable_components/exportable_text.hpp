#pragma once

#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableText : public IExportableComponent
                          , public JSON::Stringifiable <ExportableText>
                          , public JSON::Parsable <ExportableText>
    {
        std::string data;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::ExportableText,
	(std::string, data)
)
