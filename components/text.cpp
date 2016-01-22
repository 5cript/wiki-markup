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
    std::string Text::getName() const
    {
        return "Text";
    }
//-----------------------------------------------------------------------------------
    Text* Text::clone() const
    {
        return new Text(*this);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
