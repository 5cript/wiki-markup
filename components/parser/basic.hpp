#ifndef BASIC_HPP_INCLUDED
#define BASIC_HPP_INCLUDED

#include "parser_core.hpp"

namespace WikiMarkdown { namespace Components { namespace Parser { namespace Rules
{
    // declaring the dirty and global reduces compile time stress

    extern qi::rule <std::string::const_iterator> linebreak;
    extern qi::rule <std::string::const_iterator> space;

    void nameRules();

} // Rules
} // Parser
} // Components
} // WikiMarkdown

#endif // BASIC_HPP_INCLUDED
