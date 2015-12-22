#ifndef COMPONENTS_COMPONENT_HPP_INCLUDED
#define COMPONENTS_COMPONENT_HPP_INCLUDED

#include <string>

namespace WikiMarkup { namespace Components {

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual std::string toMarkup() = 0;
        virtual void fromMarkup(std::string const&) = 0;
    };

} // namespace Components
} // namespace WikiMarkup

#endif // COMPONENTS_COMPONENT_HPP_INCLUDED
