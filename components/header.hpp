#ifndef COMPONENTS_HEADER_HPP_INCLUDED
#define COMPONENTS_HEADER_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

#include <string>

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Header : public IComponent
    {
        std::string data;
        int level; // H1, H2, H3, ... = 1, 2, 3, ...

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        MetaInfo getMetaInfo() const override;
        Header* clone() const;
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
