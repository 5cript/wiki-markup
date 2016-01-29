#ifndef HORIZONTAL_LINE_HPP_INCLUDED
#define HORIZONTAL_LINE_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"
#include "parsers/parsing_results.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct HorizontalLine : public IComponent
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;
        MetaInfo getMetaInfo() const override;
        HorizontalLine* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

/*
BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::HorizontalLine
)
*/

#endif // HORIZONTAL_LINE_HPP_INCLUDED
