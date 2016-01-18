#ifndef COMPONENTS_LINK_HPP_INCLUDED
#define COMPONENTS_LINK_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "parsers/parsing_results.hpp"

#include "url.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct Link : public IComponent
    {
        bool internal;
        bool colon; // contains colon :
        bool anchor; // contains #

        std::string prefix;
        std::string localPart;
        std::vector <std::string> attributes;

        Url url;

        bool redirect;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        std::string getName() const override;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::Link,
                          internal, // 0
                          colon, // 1
                          anchor, // 2
                          prefix, // 3
                          localPart, // 4
                          attributes, // 5
                          url, // 6
                          redirect) // 7

#endif // COMPONENTS_LINK_HPP_INCLUDED
