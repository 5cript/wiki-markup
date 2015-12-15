#include "components/parser/properties.hpp"
#include "components/parser/parse.hpp"

#include <iostream>
#include <string>

int main()
{
    using namespace WikiMarkdown::Components::Parser;

    std::string data = "border=\"1\" cellpadding=\"20\"";

    using grammar = properties_grammar <
        qi_error::error_handler_cerr,
		qi_error::warning_handler_cout,
		std::decay<decltype(data)>::type::const_iterator
    >;

    auto result = parse <grammar> (data);

    for (auto const& i : result) {
        std::cout << i.first << "=" << i.second << "\n";
    }

    return 0;
}
