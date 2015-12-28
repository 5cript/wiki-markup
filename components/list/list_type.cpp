#include "list_type.hpp"

namespace WikiMarkup { namespace Components {

    ListType getTypeFromChar(char const c)
    {
        switch (c) {
            case ('#'): return LT_NUMBERED;
            case ('*'): return LT_BULLET;
            case (';'): return LT_FAT;
            case (':'): return LT_INDENT;
            default: return LT_NUMBERED; //  will never enter. parser cannot produce anything but a valid char.
        }
    }

} // namespace Components
} // namespace WikiMarkup
