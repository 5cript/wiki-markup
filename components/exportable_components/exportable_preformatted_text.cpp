#include "exportable_preformatted_text.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportablePreformattedText::toJson() const
    {
        return WikiMarkup::toJson(*this, "PreformattedText");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportablePreformattedText::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportablePreformattedText::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportablePreformattedText* ExportablePreformattedText::clone() const
    {
        return new ExportablePreformattedText(*this);
    }
//#####################################################################################################################
}
}
