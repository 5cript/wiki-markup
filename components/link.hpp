#ifndef LINK_HPP_INCLUDED
#define LINK_HPP_INCLUDED

#include "component.hpp"
#include "adaption.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct Link : public IComponent
    {
        bool internal;
        bool labeled;
        std::string label;


        std::string toMarkup() override;
        void fromMarkup(std::string const& mu) override;
    };

} // Components
} // WikiMarkup

#endif // LINK_HPP_INCLUDED
