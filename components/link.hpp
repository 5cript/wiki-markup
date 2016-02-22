#ifndef COMPONENTS_LINK_HPP_INCLUDED
#define COMPONENTS_LINK_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "../parser/qi_common/parsing_results.hpp"

#include "url.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct Link : public IComponent
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
        MetaInfo getMetaInfo() const override;
        Link* clone() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::Link,
                          internal, // 0
                          implicit, // 1
                          colon, // 2
                          anchor, // 3
                          prefix, // 4
                          localPart, // 5
                          attributes, // 6
                          url, // 7
                          redirect) // 8

#endif // COMPONENTS_LINK_HPP_INCLUDED
