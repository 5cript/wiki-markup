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

        template <typename T>
        void appendComponent(T const&& comp) {
            components_.emplace_back (new T(std::move(comp)));
        }

        std::add_lvalue_reference_t <decltype(components_)> getComponents();

        void clear();

        void dumpComponentNames(std::ostream& stream);
    };
}

#endif // PAGE_HPP_INCLUDED
