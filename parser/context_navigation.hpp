#ifndef CONTEXT_NAVIGATION_HPP_INCLUDED
#define CONTEXT_NAVIGATION_HPP_INCLUDED

#include "parser_context.hpp"

namespace WikiMarkup
{
    class ContextNavigator
    {
    public:
        /**
         *  Creates a context navigator that works on the given context.
         *  @param context A context.
         */
        ContextNavigator(ParserContext* context);

        /**
         *  Searches in the context and forwards it position until the token sequence was found.
         */
        template <typename T, typename... List>
        bool findCharSequence(T head, List... tail)
        {
            if (!ctx_->hasMoreToRead())
                return false;

            if (ctx_->get() == head)
                return findCharSequence(tail...);
            else
                return findCharSequence(head, tail...);
        }
        bool findCharSequence()
        {
            return true;
        }

        /**
         *  Checks if a certain sequence of chars starts at the current context position.
         *  This does not go forward if any of the chars does not match, as findCharSequence does.
         */
        template <typename T, typename... List>
        bool verifyCharSequence(T head, List... tail)
        {
            if (!ctx_->hasMoreToRead())
                return ctx_->getPosition();

            if (ctx_->get() == head)
                return verifyCharSequence(tail...);
            else
                return false;
        }
        bool verifyCharSequence()
        {
            return true;
        }

        /**
         *  This evaluates to true if any of the search functions ran through the whole context.
         *  The context will then also return false for "hasMoreToRead()".
         */
        bool reachedEnd() const;

    private:
        ParserContext* ctx_;
    };
}

#endif // CONTEXT_NAVIGATION_HPP_INCLUDED
