#ifndef COMPONENTS_COMPONENT_HPP_INCLUDED
#define COMPONENTS_COMPONENT_HPP_INCLUDED

#include "parsers/parsing_results.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual std::string toMarkup() = 0;
        virtual ParsingResult fromMarkup(std::string const&) = 0;
        virtual std::string getName() const = 0;
    };

} // namespace Components
} // namespace WikiMarkup

#endif // COMPONENTS_COMPONENT_HPP_INCLUDED
