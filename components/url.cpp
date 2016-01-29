#include "url.hpp"

#include <sstream>

namespace WikiMarkup { namespace Components {

    std::string Url::toString() const
    {
        std::stringstream sstr;

        sstr << scheme << ':'; // http:

        if(!authority.host.empty() || !authority.user.empty())
        {
            sstr << "//";

            if (!authority.user.empty())
                sstr << authority.user << ':' << authority.password;

            sstr << authority.host;

            if (authority.port)
                sstr << ':' << authority.port;
        }

        for (auto const& i : path)
            sstr << '/' << i;

        if (!query.empty())
            sstr << '?' << query;

        if (!fragment.empty())
            sstr << '#' << fragment;

        return sstr.str();
    }

} // namespace Components
} // namespace WikiMarkup
