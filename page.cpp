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
    std::add_lvalue_reference_t <decltype(Page::components_)> Page::getComponents()
    {
        return components_;
    }
//####################################################################################
}
