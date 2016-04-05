#ifndef PAGE_HPP_INCLUDED
#define PAGE_HPP_INCLUDED

#include "components/component.hpp"
#include "SimpleUtil/value_ptr/value_ptr.hpp"

#include <vector>
#include <memory>
#include <iosfwd>
#include <type_traits>

namespace WikiMarkup
{
    class Page
    {
    private:
        std::vector <sutil::value_ptr <Components::IComponent>> components_;

    public:
        Page() = default;
        ~Page() = default;

        /**
         *  Adds a component to the page.
         */
        template <typename T>
        void appendComponent(T const&& comp)
        {
            components_.emplace_back (new T(std::move(comp)));
        }

        /**
         *  Adds a component to the page.
         */
        void appendComponent(Components::IComponent const& component);

        /**
         *  Get all components of the page.
         */
        std::add_lvalue_reference <decltype(components_)>::type getComponents();

        /**
         *  Wipe the page clear.
         */
        void clear();

        /**
         *  Write all component type names into the stream.
         */
        std::ostream& dumpComponentNames(std::ostream& stream);

        /**
         *  Generates markup from the internal representation.
         */
        std::string toMarkup() const;
    };
}

#endif // PAGE_HPP_INCLUDED
