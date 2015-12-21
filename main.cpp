#include "components/parser/properties.hpp"
#include "components/parser/parse.hpp"
#include "components/parser/table.hpp"

#include "components/post_processors/table.hpp"

#include <iostream>
#include <string>
#include <fstream>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkdown::Components;
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
        PostProcessors::postProcessTable(result);

        std::cout << "<caption";
        for (auto const& i : result.caption.attributes)
            std::cout << " " << i.first << "=\"" << i.second << "\"";
        std::cout << ">" << result.caption.data << "</caption>\n\n";

        for (auto const& i : result.attributes)
            std::cout << i.first << ": " << i.second << "\n";

        std::cout << "\n";
        for (auto const& i : result.rows) {
            std::cout << "<row";
            for (auto const& j : i.attributes) {
                std::cout << " " << j.first << "=\"" << j.second << "\"";
            }
            std::cout << ">\n";
            for (auto const& j : i.cells) {
                std::cout << "<data";
                for (auto const& k : j.attributes) {
                    std::cout << " " << k.first << "=\"" << k.second << "\"";
                }
                std::cout << ">" << j.data << "</data>\n";

            }
            std::cout << "</row>\n";
        }
    } catch (std::exception const& exc) {
        std::cout << exc.what() << "\n";
    }


    return 0;
}
