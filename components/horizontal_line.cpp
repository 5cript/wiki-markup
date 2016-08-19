#include "horizontal_line.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(HorizontalLine)
//-----------------------------------------------------------------------------------
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
    MetaInfo HorizontalLine::getMetaInfoS()
    {
        return {
            "HorizontalLine",
            true
        };
    }
//-----------------------------------------------------------------------------------
    MetaInfo HorizontalLine::getMetaInfo() const
    {
        return HorizontalLine::getMetaInfoS();
    }
//-----------------------------------------------------------------------------------
    HorizontalLine* HorizontalLine::clone() const
    {
        return new HorizontalLine(*this);
    }
//####################################################################################

} // namespace Components
} // namespace WikiMarkup
