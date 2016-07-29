#include "text.hpp"

#include "../conversion.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Text::toMarkup()
    {
        return data;
    }
//-----------------------------------------------------------------------------------
    ParsingResult Text::fromMarkup(std::string const& mu)
    {
        data = mu;
        return ParsingResult::FULL_SUCCESS;
    }
//-----------------------------------------------------------------------------------
    std::string Text::toJson() const
    {
        return WikiMarkup::toJson(*this, getMetaInfo().name);
    }
//-----------------------------------------------------------------------------------
    void Text::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
    }
//-----------------------------------------------------------------------------------
    void Text::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//-----------------------------------------------------------------------------------
    MetaInfo Text::getMetaInfoS()
    {
        return {
            "Text",
            false
        };
    }
//-----------------------------------------------------------------------------------
    MetaInfo Text::getMetaInfo() const
    {
        return getMetaInfoS();
    }
//-----------------------------------------------------------------------------------
    Text* Text::clone() const
    {
        return new Text(*this);
    }
//-----------------------------------------------------------------------------------
    std::string Text::getRaw() const
    {
        return data;
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
