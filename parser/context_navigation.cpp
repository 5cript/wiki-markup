#include "context_navigation.hpp"

namespace WikiMarkup
{
//####################################################################################
    ContextNavigator::ContextNavigator(ParserContext* context)
        : ctx_(context)
        , positionBackup_(ctx_->getPosition())
    {

    }
//-----------------------------------------------------------------------------------
    bool ContextNavigator::reachedEnd() const
    {
        return !ctx_->hasMoreToRead();
    }
//-----------------------------------------------------------------------------------
    bool ContextNavigator::verifyCharSequence(std::string const& str)
    {
        bool result = false;
        for (auto const& i : str)
            if (i != ctx_->get())
                goto END;

        result = true;

        END:
            ctx_->setPosition(positionBackup_);
            return result;
    }
//####################################################################################
}
