#include "table.hpp"

#include "parsers/parse.hpp"
#include "parsers/table.hpp"
#include "post_processors/table.hpp"

#include <type_traits>

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Table::toMarkup()
    {
        return "table";
    }
//-----------------------------------------------------------------------------------
    void Table::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace WikiMarkup::Components::PostProcessors;

        using grammar = WikiMarkup::Components::Parser::table_grammar <
            qi_error::error_handler_cerr,
            qi_error::warning_handler_cout,
            std::decay<decltype(mu)>::type::const_iterator
        >;

        *this = parse <grammar> (mu);
        postProcessTable(*this);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
