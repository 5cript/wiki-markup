#include "list.hpp"

#include "parsers/parse.hpp"
#include "parsers/list.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string List::toMarkup()
    {
        return "list";
    }
//-----------------------------------------------------------------------------------
    void List::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(list_grammar);

        *this = parse <grammar> (mu);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
