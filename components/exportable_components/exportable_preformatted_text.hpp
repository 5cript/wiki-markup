#pragma once

#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct PreformattedLine : public JSON::Stringifiable <PreformattedLine>
                            , public JSON::Parsable <PreformattedLine>
    {
        std::string space;
        std::string data;
    };

    struct ExportablePreformattedText : public IExportableComponent
                                      , public JSON::Stringifiable <PreformattedLine>
                                      , public JSON::Parsable <PreformattedLine>
    {
        std::vector <PreformattedLine> lines;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
    };
} // namespace Components
} // namespace WikiMarkup


BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::PreformattedLine,
	(std::string, space)
	(std::string, data)
)

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::ExportablePreformattedText,
	(std::vector <WikiMarkup::Components::PreformattedLine>, lines)
)
