#include "table.hpp"

#include "parsers/parse.hpp"
#include "parsers/table.hpp"
#include "post_processors/table.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Table::toMarkup()
    {
        return "table";
    }
//-----------------------------------------------------------------------------------
    ParsingResult Table::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace WikiMarkup::Components::PostProcessors;

        TYPEDEF_GRAMMAR(table_grammar);

        auto res = parse <grammar> (mu);
        if (res.first != ParsingResult::FAIL) {
            *this = res.second;
            postProcessTable(*this);
        }
        return res.first;
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
