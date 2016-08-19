#include "text.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(Text)
//-----------------------------------------------------------------------------------
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
