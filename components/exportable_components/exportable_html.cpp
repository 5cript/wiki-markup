#include "exportable_html.hpp"

#include "../exportable_components_jspoly.hpp"
#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    ExportableHtml::ExportableHtml(HtmlTreeNode const& tree)
        : tree{tree}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    std::string ExportableHtml::toJson() const
    {
        return WikiMarkup::toJson(*this, "Html");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHtml::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableHtml::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableHtml* ExportableHtml::clone() const
    {
        return new ExportableHtml(*this);
    }
//#####################################################################################################################
}
}
