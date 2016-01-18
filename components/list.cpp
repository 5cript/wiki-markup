#include "list.hpp"

#include "parsers/parse.hpp"
#include "parsers/list.hpp"

#include "post_processors/list.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    ListTextLine::ListTextLine(std::string const& data)
        : data(data)
    {

    }
//####################################################################################
    std::string List::toMarkup()
    {
        return "list";
    }
//-----------------------------------------------------------------------------------
    ParsingResult List::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(list_grammar);

        auto res = parse <grammar> (mu);

        if (res.first != ParsingResult::FAIL)
            *this = PostProcessors::postProcessList(res.second);
        return res.first;
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
