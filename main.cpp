#include "components/parser/properties.hpp"
#include "components/parser/parse.hpp"
#include "components/parser/table.hpp"

#include <iostream>
#include <string>
#include <fstream>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkdown::Components::Parser;

    Rules::nameRules();

    std::ifstream reader ("testfile.txt", std::ios_base::binary);

    std::string data;
    do {
        char buffer[4096];
        reader.read(buffer, 4096);
        data.append(buffer, reader.gcount());
    } while (reader.gcount() == 4096);

    using grammar = table_grammar <
        qi_error::error_handler_cerr,
		qi_error::warning_handler_cout,
		std::decay<decltype(data)>::type::const_iterator
    >;

    try {
        auto result = parse <grammar> (data);

        std::cout << result.caption << "\n";
        for (auto const& i : result.attributes)
            std::cout << "\t" << i.first << ": " << i.second << "\n";
    } catch (std::exception const& exc) {
        std::cout << exc.what() << "\n";
    }


    return 0;
}
