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

    struct ExportablePreformattedText : public virtual IExportableComponent
                                      , public JSON::Stringifiable <ExportablePreformattedText>
                                      , public JSON::Parsable <ExportablePreformattedText>
    {
        std::vector <PreformattedLine> lines;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportablePreformattedText* clone() const override;

        static MetaInfo getMetaInfoS() { return {"Preformatted_Text", true}; }
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
