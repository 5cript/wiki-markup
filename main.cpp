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

    std::ofstream writer ("output.txt", std::ios_base::binary);

    try {
        auto result = parse <grammar> (data);
        PostProcessors::postProcessTable(result);

        writer << "<caption";
        for (auto const& i : result.caption.attributes)
            writer << " " << i.first << "=\"" << i.second << "\"";
        writer << ">" << result.caption.data << "</caption>\n\n";

        for (auto const& i : result.attributes)
            writer << i.first << ": " << i.second << "\n";

        writer << "\n";
        for (auto const& i : result.rows) {
            writer << "<row";
            for (auto const& j : i.attributes) {
                writer << " " << j.first << "=\"" << j.second << "\"";
            }
            writer << ">\n";
            for (auto const& j : i.cells) {
                writer << "<data";
                for (auto const& k : j.attributes) {
                    writer << " " << k.first << "=\"" << k.second << "\"";
                }
                writer << ">" << j.data << "</data>\n";

            }
            writer << "</row>\n";
        }
    } catch (std::exception const& exc) {
        std::cerr << exc.what() << "\n";
    }


    return 0;
}
