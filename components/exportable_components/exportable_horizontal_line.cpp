#include "exportable_horizontal_line.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableHorizontalLine::toJson() const
    {
        return WikiMarkup::toJson(*this, "HorizontalLine");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHorizontalLine::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHorizontalLine::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//#####################################################################################################################
}
}
