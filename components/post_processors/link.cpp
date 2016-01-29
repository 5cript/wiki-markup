#include "link.hpp"

namespace WikiMarkup { namespace Components { namespace PostProcessors {
//####################################################################################
    void postProcessLink(Link& link)
    {
        if (link.prefix == link.localPart)
        {
            link.localPart = "";
        }
    }
//####################################################################################
} // namespace PostProcessors
} // namespace Components
} // namespace WikiMarkup
