#include "comments.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/comments.hpp"

#include "../conversion.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
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
    std::string CommentText::toJson() const
    {
        return WikiMarkup::toJson(*this, getMetaInfo().name);
    }
//-----------------------------------------------------------------------------------
    void CommentText::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//-----------------------------------------------------------------------------------
    void CommentText::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
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
