#pragma once

#include "components/exportable_components/exportable_component.hpp"
#include "components/component.hpp"

namespace WikiMarkup
{
    Components::IComponent* promoteComponent(Components::IExportableComponent const* exportable);
}
