#pragma once

#include <iosfwd>

namespace WikiMarkup { namespace Components {

    enum class ListType : int
    {
        LT_NUMBERED     = 0,
        LT_BULLET       = 1,
        LT_FAT          = 2,
        LT_INDENT       = 3
    };

    std::ostream& operator<<(std::ostream& stream, ListType listType);
    std::istream& operator>>(std::istream& stream, ListType& listType);

    constexpr static const char* const ListChars = "#*;:";

    ListType getTypeFromChar(char const c);

} // namespace Components
} // namespace WikiMarkup
