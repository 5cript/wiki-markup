#pragma once

#include "list_type.hpp"
#include "list_element.hpp"
#include "list_line.hpp"
#include "list_text_line.hpp"
#include "primal_list.hpp"

#include "SimpleJSON/utility/polymorphy.hpp"

namespace WikiMarkup { namespace Components
{

}
}

JSON_DECLARE_POLYMORPHIC(WikiMarkup::Components::ListElement, (WikiMarkup::Components::ListTextLine)(WikiMarkup::Components::PrimalList))
