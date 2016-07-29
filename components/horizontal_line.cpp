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
    std::string HorizontalLine::toJson() const
    {
        return WikiMarkup::toJson(*this, getMetaInfo().name);
    }
//-----------------------------------------------------------------------------------
    void HorizontalLine::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//-----------------------------------------------------------------------------------
    void HorizontalLine::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
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
