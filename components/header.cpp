#include "header.hpp"

#include "parsers/parse.hpp"
#include "parsers/header.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Header::toMarkup()
    {
        std::string result;

        for (int i = level; i; --i)
            result.push_back('=');

        result.push_back(' ');
        result += data;
        result.push_back(' ');

        for (int i = level; i; --i)
            result.push_back('=');

        return result;
    }
//-----------------------------------------------------------------------------------
    void Header::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(header_grammar);

        *this = parse <grammar> (mu);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
