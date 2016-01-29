#ifndef UTIL_META_APPLY_HPP_INCLUDED
#define UTIL_META_APPLY_HPP_INCLUDED

#include <tuple>
#include <functional>

namespace WikiMarkup { namespace Utility {
{
    template <typename Tuple, template <typename...> class Applicant>
    struct apply { };

    template <typename... List, template <typename...> class Applicant>
    struct apply <std::tuple <List...>, Applicant>
    {
        using type = typename Applicant <List...>::type;
    };
} // Utility
} // WikiMarkup

#endif // UTIL_META_APPLY_HPP_INCLUDED
