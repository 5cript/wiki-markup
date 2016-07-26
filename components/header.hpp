#ifndef COMPONENTS_HEADER_HPP_INCLUDED
#define COMPONENTS_HEADER_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "../json_introspection.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Header : public IComponent
                  , public JSON::Stringifiable <Header>
                  , public JSON::Parsable <Header>
    {
        std::string data;
        int level; // H1, H2, H3, ... = 1, 2, 3, ...

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() override;
        void fromJson(std::string const& str) override;

        MetaInfo getMetaInfo() const override;
        Header* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Header,
    (std::string, data)
    (int, level)
)

#endif // COMPONENTS_HEADER_HPP_INCLUDED
