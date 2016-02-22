#ifndef COMPONENTS_PREFORMATTEDTEXT_HPP_INCLUDED
#define COMPONENTS_PREFORMATTEDTEXT_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "../parser/qi_common/parsing_results.hpp"

#include <string>
#include <vector>

namespace WikiMarkup { namespace Components {

    struct PreformattedLine
    {
        std::string space;
        std::string data;
    };

    struct PreformattedText : public IComponent
    {
        std::vector <PreformattedLine> lines;

        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        MetaInfo getMetaInfo() const override;
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
