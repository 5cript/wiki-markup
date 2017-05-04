#pragma once

#include "exportable_component.hpp"
#include "exportable_text.hpp"
#include "exportable_link.hpp"

namespace WikiMarkup { namespace Components {

    struct ExportableImageRegion : public IExportableComponent
                                 , public JSON::Stringifiable <ExportableText>
                                 , public JSON::Parsable <ExportableText>
    {
        std::vector <ExportableText> preImage;
        ExportableLink link;
        std::vector <ExportableText> postImage;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableImageRegion* clone() const override;

        static MetaInfo getMetaInfoS() { return {"ImageRegion", false}; }
        static std::string getRegionStartComment() { return {"WIKI_EDITOR_IMAGE_REGION_START"}; }
        static std::string getRegionEndComment() { return {"WIKI_EDITOR_IMAGE_REGION_END"}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::ExportableImageRegion,
	(std::vector <WikiMarkup::Components::ExportableText>, preImage)
    (WikiMarkup::Components::ExportableLink, link)
    (std::vector <WikiMarkup::Components::ExportableText>, postImage)
)
