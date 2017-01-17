#pragma once

#include "components/exportable_components/exportable_component.hpp"
#include "SimpleJSON/utility/object.hpp"
#include "dll.h"

namespace WikiMarkup
{
    DLL_EXPORT Components::IExportableComponent* createExportableComponent(std::string const& type, JSON::ObjectReader const& jsonData);
}
