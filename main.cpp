#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"

#include "components/parsers/parse.hpp"
//#include "components/parsers/indents.hpp"
//#include "components/parsers/format.hpp"
//#include "components/parsers/comments.hpp"
#include "components/parsers/list.hpp"

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

    /*
    Table table;
    table.fromMarkup(data);
    */

    using namespace WikiMarkup::Components::Parser;

    TYPEDEF_GRAMMAR(list_grammar);

    auto result = parse <grammar> (data);

    std::function <void(List const&, int)> printList;
    printList = [&printList](List const& list, int depth) {
        for (int i = 0; i != depth; ++i)
            std::cout << '\t';
        std::cout << "type: " << list.type << "\n";

        for (int i = 0; i != depth; ++i)
            std::cout << '\t';
        std::cout << "data: " << list.data << "\n";

        if (!list.child.empty()) {
            for (int i = 0; i != depth; ++i)
                std::cout << '\t';
            std::cout << "child: " << "\n";
            printList(list.child[0], depth + 1);
        }

        if (!list.subList.empty()) {
            for (int i = 0; i != depth; ++i)
                std::cout << '\t';
            std::cout << "subList: " << "\n";
            printList(list.subList[0], depth + 1);
        }


        std::cout << "------------------------\n";
    };

    printList(result, 0);

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
