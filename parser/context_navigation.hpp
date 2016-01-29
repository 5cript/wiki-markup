#ifndef CONTEXT_NAVIGATION_HPP_INCLUDED
#define CONTEXT_NAVIGATION_HPP_INCLUDED

#include "parser_context.hpp"

#include <utility>
#include <type_traits>

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
            return findCharSequenceImpl <std::tuple <T, List...>> (head, tail...);
        }

        /**
         *  Checks if a certain sequence of chars starts at the current context position.
         *  This function does not change the context position.
         */
        template <typename T, typename... List,
                  typename = typename std::enable_if <std::is_same <T, char>::value>::type>
        bool verifyCharSequence(T head, List... tail)
        {
            if (!ctx_->hasMoreToRead())
                return ctx_->getPosition();

            if (ctx_->get() == head)
                return verifyCharSequence(tail...); // first char matches, now continue with second.
            else {
                ctx_->setPosition(positionBackup_); // reset position, as if nothing happened.
                return false;
            }
        }
        bool verifyCharSequence()
        {
            ctx_->setPosition(positionBackup_); // reset position, as if nothing happened.
            return true;
        }
        bool verifyCharSequence(std::string const& str);

        /**
         *  This evaluates to true if any of the search functions ran through the whole context.
         *  The context will then also return false for "hasMoreToRead()".
         */
        bool reachedEnd() const;

    private:
        template <typename List, int Pos = 0>
        bool findCharSequenceImpl(List const& list)
        {
            if (!ctx_->hasMoreToRead())
                return false;

            if (ctx_->get() == std::get <Pos> (list))
                return findCharSequenceImpl <List, Pos+1> (list);
            else
                return findCharSequenceImpl(list);
        }

        bool findCharSequenceImpl()
        {
            positionBackup_ = ctx_->getPosition();
            return true;
        }

    private:
        ParserContext* ctx_;

        /** This is set to the context position on navigator construction.
         *  And is always changed, when the navigator successfully moves the context position.
         **/
        ParserContext::position_type positionBackup_;
    };
}

#endif // CONTEXT_NAVIGATION_HPP_INCLUDED
