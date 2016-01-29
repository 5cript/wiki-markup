#include "text.hpp"

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
    MetaInfo Text::getMetaInfo() const
    {
        return {
            "Text",
            false
        };
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
