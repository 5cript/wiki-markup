#include "main.hpp"

#include "parser/core.hpp"
#include "parser/table.hpp"

#include <iostream>
#include <string>
#include <fstream>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkup::Parser;

    init();

    auto data = readStringFromFile ("testfile.txt");
    auto res = parseTable(data);


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
