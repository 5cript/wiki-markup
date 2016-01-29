#include "page.hpp"

#include <iostream>

namespace WikiMarkup
{
//####################################################################################
    void Page::dumpComponentNames(std::ostream& stream)
    {
        for (auto const& i : components_) {
            stream << i->getName() << " ";
        }
    }
//-----------------------------------------------------------------------------------
    void Page::clear()
    {
        components_.clear();
    }
//-----------------------------------------------------------------------------------
    void Page::appendComponent(Components::IComponent const& component)
    {
        components_.emplace_back(component.clone());
    }
//-----------------------------------------------------------------------------------
    std::add_lvalue_reference_t <decltype(Page::components_)> Page::getComponents()
    {
        return components_;
    }
//-----------------------------------------------------------------------------------
    std::string Page::toMarkup() const
    {
        std::string result;
        for (auto const& i : components_)
        {
            result += i->toMarkup();
        }
        return result;
    }
//####################################################################################
}
