#ifndef LIST_TYPE_HPP_INCLUDED
#define LIST_TYPE_HPP_INCLUDED

namespace WikiMarkup { namespace Components {

    enum ListType
    {
        LT_NUMBERED     = 0b0001,
        LT_BULLET       = 0b0010,
        LT_LINE_ONLY    = 0b0100,
        LT_INDENT       = 0b1000
    };

} // namespace Components
} // namespace WikiMarkup

#endif // LIST_TYPE_HPP_INCLUDED
