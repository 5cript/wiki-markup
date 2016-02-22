#include "main.hpp"

#include "configuration.hpp"
#include "peripherals/parsers/style/color.hpp"
#include "parser/qi_common/parse.hpp"
#include "peripherals/style/attribute_definition.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <functional>

// https://www.mediawiki.org/wiki/Markup_spec/EBNF

int main()
{
    using namespace WikiMarkup;
    using namespace Peripherals;
    using namespace Style;
    using namespace Parser;

    auto data = readStringFromFile ("testfile.txt");

    TYPEDEF_GRAMMAR(color_grammar);
    auto res = parse <grammar> (data);
    auto color = res.second;

    std::cout << "rgb(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << color.a << ")\n";

    /*
    PageParser parser (data);
    parser.parse();

    Page p = parser.getPage();
    //p.dumpComponentNames(std::cout);
    //std::cout << p.toMarkup();

    auto& components = p.getComponents();

    for (auto const& i : components)
    {
        if (i->getMetaInfo().name == "Table")
        {
            auto* table = dynamic_cast <Table*> (i.get());
            auto stripped = stripHeaders(*table);
            auto horiz = getHorizontalHeaders(*table);
            auto verti = getVerticalHeaders(*table);

            for (auto const& i : stripped.rows)
            {
                for (auto const& j : i.cells)
                {
                    std::cout << j.data << "; ";
                }
                std::cout << "\n";
            }

            break;
        }
    }
    */

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
