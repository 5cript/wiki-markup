#include "context_navigation.hpp"

namespace WikiMarkup
{
//####################################################################################
    DLL_EXPORT ContextNavigator::ContextNavigator(ParserContext* context)
        : ctx_(context)
        , positionBackup_(ctx_->getPosition())
    {

    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT bool ContextNavigator::reachedEnd() const
    {
        return !ctx_->hasMoreToRead();
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT bool ContextNavigator::verifyCharSequence(std::string const& str)
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
