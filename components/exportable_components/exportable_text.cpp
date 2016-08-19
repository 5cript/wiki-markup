#include "exportable_text.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableText::toJson() const
    {
        return WikiMarkup::toJson(*this, "Text");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableText::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableText::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//#####################################################################################################################
}
}
