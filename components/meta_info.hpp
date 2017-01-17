#pragma once

#include <string>

namespace WikiMarkup { namespace Components {

    struct MetaInfo
    {
        std::string name;
        bool isSection;

        MetaInfo(std::string name, bool isSection);
    };

} // namespace Components
} // namespace WikiMarkup
