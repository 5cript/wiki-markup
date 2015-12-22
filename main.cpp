#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"

#include "components/parsers/parse.hpp"
//#include "components/parsers/indents.hpp"
//#include "components/parsers/format.hpp"
//#include "components/parsers/comments.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkup;
    using namespace Components;

    auto data = readStringFromFile ("testfile.txt");

    /*
    Table table;
    table.fromMarkup(data);
    */

    using namespace WikiMarkup::Components::Parser;

    TYPEDEF_GRAMMAR(comment_grammar);

    auto vec = parse <grammar> (data);
    for (auto const& i : vec) {
        std::cout << i.data << ":(" << std::boolalpha << i.isComment << ")\n";
    }

    return 0;
}

std::string readStringFromFile(std::string const& fileName)
{
    std::ifstream reader (fileName, std::ios_base::binary);

    std::string data;
    do {
        char buffer[4096];
        reader.read(buffer, 4096);
        data.append(buffer, reader.gcount());
    } while (reader.gcount() == 4096);

    return data;
}
