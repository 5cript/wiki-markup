#ifndef COMPONENTS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_COMMENTS_HPP_INCLUDED

#include "adaption.hpp"
#include "component.hpp"

namespace WikiMarkup { namespace Components {

    struct CommentText : public IComponent
    {
        std::string data;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::CommentText, data
)

#endif // COMPONENTS_COMMENTS_HPP_INCLUDED
