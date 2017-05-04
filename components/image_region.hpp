#pragma once

#include "component.hpp"
#include "exportable_components/exportable_image_region.hpp"

namespace WikiMarkup { namespace Components
{
    struct ImageRegion : public IComponent
                       , public ExportableImageRegion
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        ImageRegion* clone() const override;
    };

}
}

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::ImageRegion, preImage, link, postImage)
