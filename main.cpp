#include "main.hpp"
//#include "components/table.hpp"
//#include "components/header.hpp"
#include "components/list.hpp"


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

    // using namespace WikiMarkup::Components::Parser;

    List list;
    list.fromMarkup(data);

    std::function <void(List const&, int)> printList;
    printList = [&](List const& curList, int depth) {
        for (auto const& i : curList.elements) {
            ListTextLine* tex = dynamic_cast <ListTextLine*> (i.get());
            if (tex) {
                for (int i = 0; i != depth; ++i)
                    std::cout << "  ";
                std::cout << tex->data;
            } else {
                //std::cout << "list";
                printList(*dynamic_cast <List*> (i.get()), depth + 1);
            }
            std::cout << "\n";
        }
    };

    printList(list, 0);

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
