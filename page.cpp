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
//####################################################################################
}
