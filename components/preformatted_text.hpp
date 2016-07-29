#ifndef COMPONENTS_PREFORMATTEDTEXT_HPP_INCLUDED
#define COMPONENTS_PREFORMATTEDTEXT_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "../json_introspection.hpp"

#include <string>
#include <vector>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct PreformattedLine : public JSON::Stringifiable <PreformattedLine>
                            , public JSON::Parsable <PreformattedLine>
    {
        std::string space;
        std::string data;
    };

    struct PreformattedText : public IComponent
                            , public JSON::Stringifiable <PreformattedLine>
                            , public JSON::Parsable <PreformattedLine>
    {
        std::vector <PreformattedLine> lines;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        PreformattedText* clone() const override;
        std::string getRaw() const;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::PreformattedLine, space, data
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::PreformattedText, lines
)

#endif // COMPONENTS_PREFORMATTEDTEXT_HPP_INCLUDED
