#ifndef COMPONENTS_LINK_HPP_INCLUDED
#define COMPONENTS_LINK_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "url.hpp"
#include "../json_introspection.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Link : public IComponent,
                  public JSON::Stringifiable <Link>,
                  public JSON::Parsable <Link>
    {
        bool internal;
        bool implicit;
        bool colon; // contains colon :
        bool anchor; // contains #

        std::string prefix;
        std::string localPart;
        std::vector <std::string> attributes;

        Url url;

        bool redirect;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        Link* clone() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Link,
    (bool,                          internal)   // 0
    (bool,                          implicit)   // 1
    (bool,                          colon)      // 2
    (bool,                          anchor)     // 3
    (std::string,                   prefix)     // 4
    (std::string,                   localPart)  // 5
    (std::vector <std::string>,     attributes) // 6
    (WikiMarkup::Components::Url,   url)        // 7
    (bool,                          redirect)   // 8
)

#endif // COMPONENTS_LINK_HPP_INCLUDED
