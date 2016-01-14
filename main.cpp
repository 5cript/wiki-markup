#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"
//#include "components/list.hpp"

#include "components/parsers/parse.hpp"
#include "components/parsers/url.hpp"
#include "components/parsers/link.hpp"


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

    using namespace WikiMarkup::Components::Parser;

    TYPEDEF_GRAMMAR(link_grammar);

    try {
        auto result = parse <grammar> (data, true, true);

        std::cout << "internal: " << result.internal << "\n";
        std::cout << "colon: " << result.colon << "\n";
        std::cout << "anchor: " << result.anchor << "\n";
        std::cout << "prefix: " << result.prefix << "\n";
        std::cout << "localPart: " << result.localPart << "\n";
        std::cout << "attributes: \n";
        for (auto const& i : result.attributes)
            std::cout << "\t" << i << "\n";
        std::cout << "redirect: " << result.redirect << "\n";


        std::cout << "url.scheme: " << result.url.scheme << "\n";
        std::cout << "url.authority.user: " << result.url.authority.user << "\n";
        std::cout << "url.authority.password: " << result.url.authority.password << "\n";
        std::cout << "url.authority.host: " << result.url.authority.host << "\n";
        std::cout << "url.authority.port: " << result.url.authority.port << "\n";
        std::cout << "url.path: ";
        for (auto const& i : result.url.path)
             std::cout << i << "/";
        std::cout << "\n";
        std::cout << "url.query: " << result.url.query << "\n";
        std::cout << "url.fragment: " << result.url.fragment << "\n";
    } catch (std::exception const& exc) {
        std::cout << exc.what() << "\n";
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

std::vector <std::string> readLinesFromFile(std::string const& fileName)
{
    std::ifstream reader (fileName);

    std::string line;
    std::vector <std::string> lines;
    while (std::getline(reader, line))
        lines.push_back(line);

    return lines;
}
