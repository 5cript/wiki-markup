#pragma once

#include "exportable_components/exportable_comment.hpp"

#include "component.hpp"

namespace WikiMarkup { namespace Components
{
    struct CommentText : public IComponent
                       , public ExportableCommentText
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        CommentText* clone() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::CommentText,
	(std::string, data)
)
