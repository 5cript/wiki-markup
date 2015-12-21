#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser { namespace Rules
{
    qi::rule <std::string::const_iterator> linebreak = qi::lit("\r\n") || qi::char_('\n') || qi::char_('\r');
    qi::rule <std::string::const_iterator> space = qi::char_(' ') || qi::char_('\t');

    void nameRules()
    {
        linebreak.name("linebreak");
        space.name("space");
    }

} // Rules
} // Parser
} // Components
} // WikiMarkup

