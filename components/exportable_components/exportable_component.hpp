#pragma once

#include <string>
#include "SimpleJSON/utility/object.hpp"
#include "../adaption.hpp"
#include "../../json_introspection.hpp"

#include "../meta_info.hpp"

namespace WikiMarkup { namespace Components
{
    class IExportableComponent
    {
    public:
        virtual std::string toJson() const = 0;
        virtual void fromJson(std::string const&) = 0;
        virtual void fromJson(JSON::ObjectReader const& reader) = 0;

        virtual IExportableComponent* clone() const = 0;
    };
}
}
