#pragma once

#include "exportable_component.hpp"
#include "../adaption.hpp"
#include "../../json_introspection.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableCommentText : public IExportableComponent
                                 , public JSON::Stringifiable <ExportableCommentText>
                                 , public JSON::Parsable <ExportableCommentText>
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
    WikiMarkup::Components::ExportableCommentText,
    (std::string, data)
)
