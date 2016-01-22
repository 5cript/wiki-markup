#include "context_navigation.hpp"

namespace WikiMarkup
{
//####################################################################################
    ContextNavigator::ContextNavigator(ParserContext* context)
        : ctx_(context)
    {

    }
//-----------------------------------------------------------------------------------
    bool ContextNavigator::reachedEnd() const
    {
        return !ctx_->hasMoreToRead();
    }
//####################################################################################
}
