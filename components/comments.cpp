#include "comments.hpp"

#include "parsers/parse.hpp"
#include "parsers/comments.hpp"

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

        TYPEDEF_GRAMMAR(comment_grammar);

        auto res = parse <grammar> (mu);
        *this = res.second;
        return res.first;
    }
//-----------------------------------------------------------------------------------
    MetaInfo CommentText::getMetaInfo() const
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
