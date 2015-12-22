#ifndef COMPONENTS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_COMMENTS_HPP_INCLUDED

namespace WikiMarkup { namespace Components {

    struct CommentText
    {
        std::string data;
        bool isComment;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::CommentText,
    (std::string, data)
    (bool, isComment)
)

#endif // COMPONENTS_COMMENTS_HPP_INCLUDED
