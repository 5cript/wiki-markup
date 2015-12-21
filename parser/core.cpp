#include "core.hpp"
#include "../components/parsers/basic.hpp"

namespace WikiMarkup { namespace Parser {

    void init()
    {
        WikiMarkup::Components::Parser::Rules::nameRules();
    }

} // Parser
} // WikiMarkup
