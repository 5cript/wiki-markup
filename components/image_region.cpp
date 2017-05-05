#include "image_region.hpp"

#include "comments.hpp"
#include "text.hpp"
#include "link.hpp"

#include "../promote_component.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(ImageRegion)
//---------------------------------------------------------------------------------------------------------------------
    std::string ImageRegion::toMarkup()
    {
        auto comment = [this](std::string const& text)
        {
            auto comment = CommentText{};
            comment.data = text;
            return comment;
        };

        std::string result;
        result += comment(getRegionStartComment()).toMarkup();
        for (auto const& i : preImage)
        {
            std::unique_ptr <IComponent> promoted {promoteComponent(&i)};
            result += promoted->toMarkup();
        }
        Link l;
        l.fromJson(link.toJson());
        result += l.toMarkup();
        for (auto const& i : postImage)
        {
            std::unique_ptr <IComponent> promoted {promoteComponent(&i)};
            result += promoted->toMarkup();
        }
        result += comment(getRegionEndComment()).toMarkup();

        return result;
    }
//---------------------------------------------------------------------------------------------------------------------
    ParsingResult ImageRegion::fromMarkup(std::string const&)
    {
        return ParsingResult::FAIL;
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo ImageRegion::getMetaInfo() const
    {
        return getMetaInfoS();
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo ImageRegion::getMetaInfoS()
    {
        return {
            "ImageRegion",
            true
        };
    }
//---------------------------------------------------------------------------------------------------------------------
    ImageRegion* ImageRegion::clone() const
    {
        return new ImageRegion(*this);
    }
//#####################################################################################################################
}
}
