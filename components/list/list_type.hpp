#ifndef LIST_TYPE_HPP_INCLUDED
#define LIST_TYPE_HPP_INCLUDED

namespace WikiMarkup { namespace Components {

    enum ListType
    {
        LT_NUMBERED     = 0,
        LT_BULLET       = 1,
        LT_FAT          = 2,
        LT_INDENT       = 3
    };

    constexpr static const char* const ListChars = "#*;:";

    ListType getTypeFromChar(char const c);

} // namespace Components
} // namespace WikiMarkup

#endif // LIST_TYPE_HPP_INCLUDED
