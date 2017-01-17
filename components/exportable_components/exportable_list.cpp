#include "exportable_list.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableList::toJson() const
    {
        return WikiMarkup::toJson(*this, "List");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableList::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableList::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableList* ExportableList::clone() const
    {
        return new ExportableList(*this);
    }
//#####################################################################################################################
}
}
