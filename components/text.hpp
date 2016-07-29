#ifndef COMPONENTS_TEXT_HPP_INCLUDED
#define COMPONENTS_TEXT_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "../json_introspection.hpp"

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Text : public IComponent
                , public JSON::Stringifiable <Text>
                , public JSON::Parsable <Text>
    {
        std::string data;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;

        MetaInfo getMetaInfo() const override;
        Text* clone() const override;
        std::string getRaw() const;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::Text, data)

#endif // COMPONENTS_TEXT_HPP_INCLUDED
