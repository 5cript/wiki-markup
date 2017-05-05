#pragma once

#include "exportable_component.hpp"

#include "../list/list_atomics.hpp"

#include <string>
#include <vector>
#include <memory>

namespace WikiMarkup { namespace Components
{
    struct ExportableList : public virtual IExportableComponent
                          , public JSON::Stringifiable <ExportableList>
                          , public JSON::Parsable <ExportableList>
    {
        PrimalList list;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableList* clone() const override;

        static MetaInfo getMetaInfoS() { return {"List", true}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableList,
    (WikiMarkup::Components::PrimalList, list)
)
