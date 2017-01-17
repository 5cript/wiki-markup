#include "exportable_header.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableHeader::toJson() const
    {
        return WikiMarkup::toJson(*this, "Header");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHeader::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHeader::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableHeader* ExportableHeader::clone() const
    {
        return new ExportableHeader(*this);
    }
//#####################################################################################################################
}
}
