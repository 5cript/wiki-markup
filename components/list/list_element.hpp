#pragma once

namespace WikiMarkup { namespace Components
{
    struct ListElement
    {
        virtual ~ListElement() = default;
        virtual ListElement* clone() const = 0;
    };
}
}
