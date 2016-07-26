#include "horizontal_line.hpp"

#include "../conversion.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string HorizontalLine::toMarkup()
    {
        return "----";
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
    std::string HorizontalLine::toJson()
    {
        return toJson(*this, getMetaInfo().name);
    }
//-----------------------------------------------------------------------------------
    void HorizontalLine::fromJson(std::string const& str)
    {
        fromJson(*this, str);
    }
//-----------------------------------------------------------------------------------
    MetaInfo HorizontalLine::getMetaInfo() const
    {
        return {
            "HorizontalLine",
            true
        };
    }
//-----------------------------------------------------------------------------------
    HorizontalLine* HorizontalLine::clone() const
    {
        return new HorizontalLine(*this);
    }
//####################################################################################

} // namespace Components
} // namespace WikiMarkup
