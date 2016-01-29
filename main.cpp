#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"
//#include "components/list.hpp"
#include "components/link.hpp"

//#include "components/parsers/parse.hpp"
//#include "components/parsers/url.hpp"
#include "components/parsers/link.hpp"

#include "configuration.hpp"
#include "parser/page_parser.hpp"


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <functional>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkup;
    using namespace Components;

    auto data = readStringFromFile ("testfile.txt");

    PageParser parser (data);
    parser.parse();

    Page p = parser.getPage();
    //p.dumpComponentNames(std::cout);
    std::cout << p.toMarkup();

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

std::vector <std::string> readLinesFromFile(std::string const& fileName)
{
    std::ifstream reader (fileName);

    std::string line;
    std::vector <std::string> lines;
    while (std::getline(reader, line))
        lines.push_back(line);

    return lines;
}
