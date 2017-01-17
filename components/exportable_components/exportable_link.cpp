#include "exportable_link.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableLink::toJson() const
    {
        return WikiMarkup::toJson(*this, "Link");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableLink::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableLink::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableLink* ExportableLink::clone() const
    {
        return new ExportableLink(*this);
    }
//#####################################################################################################################
}
}
