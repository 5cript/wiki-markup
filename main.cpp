#include "main.hpp"

#include "configuration.hpp"

#include "twisted-spirit/core/parse.hpp"
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
    using namespace TwistedSpirit;

    std::cout << "Test\n";

    auto data = readStringFromFile ("testfile.txt");

    WikiMarkup::PageParser parser (data);
    parser.parse();

    std::cout << parser.getPage().toJson() << "\n";

    /*
    auto page = parser.getPage();

    std::stringstream sstr;
    std::ofstream writer("page_res.txt", std::ios_base::binary);
    sstr << page.toJson();
    writer << sstr.str();

    WikiMarkup::Page page2;
    page2.fromJson(sstr.str());

    page2.dumpComponentNames(std::cout);
    */

    /*
    TYPEDEF_GRAMMAR(color_grammar);
    auto res = parse <grammar> (data);
    auto color = res.second;

    std::cout << "rgb(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << color.a << ")\n";
    */

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
