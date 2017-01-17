#include "list_text_line.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    ListTextLine::ListTextLine(std::string const& data)
        : data(data)
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    ListTextLine* ListTextLine::clone() const
    {
        return new ListTextLine(*this);
    }
//#####################################################################################################################
}
}
