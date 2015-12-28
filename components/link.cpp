#include "link.hpp"

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Link::toMarkup()
    {
        return "link";
    }
//-----------------------------------------------------------------------------------
    void Link::fromMarkup(std::string const& mu)
    {
        /*
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(list_grammar);

        auto plainList = parse <grammar> (mu);

        *this = PostProcessors::postProcessList(plainList);
        */
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
