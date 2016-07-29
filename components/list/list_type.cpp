#include "list_type.hpp"

#include <iostream>

namespace WikiMarkup { namespace Components {
//#####################################################################################################################
    ListType getTypeFromChar(char const c)
    {
        switch (c) {
            case ('#'): return ListType::LT_NUMBERED;
            case ('*'): return ListType::LT_BULLET;
            case (';'): return ListType::LT_FAT;
            case (':'): return ListType::LT_INDENT;
            default: return ListType::LT_NUMBERED; //  will never enter. parser cannot produce anything but a valid char.
        }
    }
//---------------------------------------------------------------------------------------------------------------------
    std::ostream& operator<<(std::ostream& stream, ListType listType)
    {
        stream << (int)listType;
        return stream;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::istream& operator>>(std::istream& stream, ListType& listType)
    {
        int type;
        stream >> type;
        listType = static_cast <ListType> (type);
        return stream;
    }
//#####################################################################################################################
} // namespace Components
} // namespace WikiMarkup
