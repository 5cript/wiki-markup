#include "exportable_comment.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableCommentText::toJson() const
    {
        return WikiMarkup::toJson(*this, "CommentText");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableCommentText::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableCommentText::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableCommentText* ExportableCommentText::clone() const
    {
        return new ExportableCommentText(*this);
    }
//#####################################################################################################################
}
}
