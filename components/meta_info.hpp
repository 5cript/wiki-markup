#ifndef COMPONENTS_META_INFO_HPP_INCLUDED
#define COMPONENTS_META_INFO_HPP_INCLUDED

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

#endif // COMPONENTS_META_INFO_HPP_INCLUDED
