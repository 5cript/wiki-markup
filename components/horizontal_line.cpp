#include "horizontal_line.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string HorizontalLine::toMarkup()
    {
        return "----\n";
    }
//-----------------------------------------------------------------------------------
    ParsingResult HorizontalLine::fromMarkup(std::string const& mu)
    {
        // using qi for this? you kiddin?
        if (mu != "----")
            return ParsingResult::FAIL;
        else
            return ParsingResult::FULL_SUCCESS;
    }
//-----------------------------------------------------------------------------------
    std::string HorizontalLine::getName() const
    {
        return "HorizontalLine";
    }
//-----------------------------------------------------------------------------------
    HorizontalLine* HorizontalLine::clone() const
    {
        return new HorizontalLine(*this);
    }
//####################################################################################

} // namespace Components
} // namespace WikiMarkup
