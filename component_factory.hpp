#pragma once

#include "components/component.hpp"
#include "SimpleJSON/utility/object.hpp"

namespace WikiMarkup
{
    Components::IComponent* createComponent(std::string const& type, JSON::ObjectReader const& jsonData);
}
