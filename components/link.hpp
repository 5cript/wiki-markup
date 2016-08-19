#ifndef COMPONENTS_LINK_HPP_INCLUDED
#define COMPONENTS_LINK_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include "exportable_components/exportable_link.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Link : public IComponent
                , public ExportableLink
    {

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

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
