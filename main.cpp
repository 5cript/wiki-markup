#include "components/parser/properties.hpp"
#include "components/parser/parse.hpp"
#include "components/parser/table.hpp"

#include <iostream>
#include <string>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkdown::Components::Parser;

    Rules::nameRules();

    std::string data = "{|\n";

    using grammar = table_grammar <
        qi_error::error_handler_cerr,
		qi_error::warning_handler_cout,
		std::decay<decltype(data)>::type::const_iterator
    >;

    auto result = parse <grammar> (data);


    return 0;
}
