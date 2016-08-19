#include "comments.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/comments.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(CommentText)
//-----------------------------------------------------------------------------------
    std::string CommentText::toMarkup()
    {
        return std::string("<!--") + data + "-->";
    }
//-----------------------------------------------------------------------------------
    ParsingResult CommentText::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(comment_grammar);

        auto res = TwistedSpirit::parse <grammar> (mu);
        *this = res.second;
        return res.first;
    }
//-----------------------------------------------------------------------------------
    MetaInfo CommentText::getMetaInfo() const
    {
        return getMetaInfoS();
    }
//-----------------------------------------------------------------------------------
    MetaInfo CommentText::getMetaInfoS()
    {
        return {
            "CommentText",
            false
        };
    }
//-----------------------------------------------------------------------------------
    CommentText* CommentText::clone() const
    {
        return new CommentText(*this);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
