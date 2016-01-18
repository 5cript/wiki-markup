#ifndef PAGE_HPP_INCLUDED
#define PAGE_HPP_INCLUDED

#include "components/component.hpp"

#include <vector>
#include <memory>

namespace WikiMarkup
{
    class Page
    {
    public:
        Page() = default;
        ~Page() = default;

        template <typename T>
        void appendComponent(T const& comp) {
            components_.emplace_back (new T(comp));
        }

    private:
        std::vector <std::unique_ptr <Components::IComponent>> components_;
    };
}

#endif // PAGE_HPP_INCLUDED
