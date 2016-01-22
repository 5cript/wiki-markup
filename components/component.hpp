#pragma once

#include "../../SimpleUtil/value_ptr/cloneable.hpp"
#include "parsers/parsing_results.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    using namespace sutil;

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual std::string toMarkup() = 0;
        virtual ParsingResult fromMarkup(std::string const&) = 0;
        virtual std::string getName() const = 0;
        virtual IComponent* clone() const = 0;
    };

} // namespace Components
} // namespace WikiMarkup
