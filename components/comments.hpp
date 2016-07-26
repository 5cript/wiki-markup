#ifndef COMPONENTS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_COMMENTS_HPP_INCLUDED

#include "adaption.hpp"
#include "component.hpp"

#include "../json_introspection.hpp"

namespace WikiMarkup { namespace Components {

    struct CommentText : public IComponent,
                         public JSON::Parsable <CommentText>,
                         public JSON::Stringifiable <CommentText>
    {
        std::string data;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() override;
        void fromJson(std::string const& str) override;

        MetaInfo getMetaInfo() const override;
        CommentText* clone() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::CommentText,
	(std::string, data)
)

#endif // COMPONENTS_COMMENTS_HPP_INCLUDED
