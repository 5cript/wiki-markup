#pragma once

#include <string>
#include "../adaption.hpp"
#include "../../json_introspection.hpp"

#include "SimpleJSON/utility/object.hpp"
#include "SimpleJSON/utility/polymorphy.hpp"

#include "SimpleUtil/value_ptr/value_ptr.hpp"

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

        virtual ~IExportableComponent() = default;
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::IExportableComponent
)
