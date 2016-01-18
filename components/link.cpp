#include "link.hpp"

#include "parsers/parse.hpp"
#include "parsers/link.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Link::toMarkup()
    {
        return "link";
    }
//-----------------------------------------------------------------------------------
    ParsingResult Link::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(link_grammar);

        auto res = parse <grammar> (mu);
        *this = res.second;
        return res.first;
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
