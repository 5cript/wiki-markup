#include "exportable_table.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableTable::toJson() const
    {
        return WikiMarkup::toJson(*this, "Table");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableTable::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableTable::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//#####################################################################################################################
}
}
