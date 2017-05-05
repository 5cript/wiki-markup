#pragma once

#include "exportable_component.hpp"
#include "exportable_text.hpp"
#include "exportable_link.hpp"
#include "exportable_html.hpp"
#include "exportable_list.hpp"

#include "SimpleUtil/value_ptr/value_ptr.hpp"

#include "SimpleJSON/utility/polymorphy.hpp"
#include "SimpleJSON/stringify/jss_smart_ptr.hpp"
#include "SimpleJSON/parse/jsd_smart_ptr.hpp"

namespace WikiMarkup { namespace Components
{
    struct ExportableRichText : public virtual IExportableComponent
                              , public JSON::Stringifiable <ExportableRichText>
                              , public JSON::Parsable <ExportableRichText>
    {
        std::vector <sutil::value_ptr <IExportableComponent> > subelements;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableRichText* clone() const override;

        static MetaInfo getMetaInfoS() { return {"RichText", false}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableRichText,
    (std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent> >, subelements)
    //(sutil::value_ptr <WikiMarkup::Components::IExportableComponent>, subelements)
    //(WikiMarkup::Components::IExportableComponent*, subelements)
)
