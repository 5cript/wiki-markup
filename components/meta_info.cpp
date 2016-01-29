#include "meta_info.hpp"

namespace WikiMarkup { namespace Components {

    MetaInfo::MetaInfo(std::string name, bool isSection)
        : name(std::move(name))
        , isSection(isSection)
    {

    }

} // namespace Components
} // namespace WikiMarkup
