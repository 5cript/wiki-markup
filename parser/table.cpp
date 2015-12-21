#include "table.hpp"

#include "../components/parsers/parse.hpp"
#include "../components/parsers/table.hpp"
#include "../components/post_processors/table.hpp"

namespace WikiMarkup { namespace Parser {

    Components::Holders::Table parseTable(std::string const& table)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace WikiMarkup::Components::PostProcessors;

        using grammar = WikiMarkup::Components::Parser::table_grammar <
            qi_error::error_handler_cerr,
            qi_error::warning_handler_cout,
            std::decay<decltype(table)>::type::const_iterator
        >;

        auto result = parse <grammar> (table);
        postProcessTable(result);
        return result;
    }

} // Parser
} // WikiMarkup
