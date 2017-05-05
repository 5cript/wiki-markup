#pragma once

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
        virtual ~Page() = default;

        /**
         *  Adds a component to the page.
         */
        template <typename T>
        void appendComponent(T const&& comp)
        {
            components_.emplace_back (new T(std::move(comp)));
        }

        /**
         *  Appends one page to another.
         */
        Page& operator+=(Page const& page)
        {
            auto const& components = page.getComponents();
            for (auto const& i : components)
                appendComponent(i->clone());
            return *this;
        }

        /**
         *  Adds a component to the page.
         */
        void appendComponent(Components::IComponent const& component);

        /**
         *  Adds a component to the page.
         */
        void appendComponent(Components::IComponent* component);

        /**
         *  Get all components of the page.
         */
        std::add_lvalue_reference <decltype(components_)>::type getComponents();

        /**
         *  Get all (immutable) components of the page.
         */
        std::add_lvalue_reference <decltype(components_) const>::type getComponents() const;

        /**
         *  Wipe the page clear.
         */
        void clear();

        /**
         *  Write all component type names into the stream.
         */
        std::ostream& dumpComponentNames(std::ostream& stream);

        /**
         *  Generates a json string from the internal representation.
         */
        std::string toJson() const;

        /**
         *  Generates the components from JSON.
         */
        void fromJson(std::string const& json);

        /**
         *  Generates markup from the internal representation.
         */
        std::string toMarkup() const;
    };
}
