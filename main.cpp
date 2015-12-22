#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"
#include "components/parsers/indents.hpp"

#include <iostream>
#include <string>
#include <fstream>

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
    using namespace WikiMarkup::Components::PostProcessors;

    TYPEDEF_GRAMMAR(indents_grammar);

    auto str = parse <grammar> (data);
    std::cout << str;


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
