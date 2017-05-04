#include "exportable_image_region.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableImageRegion::toJson() const
    {
        return WikiMarkup::toJson(*this, "ImageRegion");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableImageRegion::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableImageRegion::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableImageRegion* ExportableImageRegion::clone() const
    {
        return new ExportableImageRegion(*this);
    }
//#####################################################################################################################
}
}
