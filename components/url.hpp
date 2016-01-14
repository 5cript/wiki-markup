#ifndef COMPONENTS_URL_HPP_INCLUDED
#define COMPONENTS_URL_HPP_INCLUDED

#include "adaption.hpp"

#include <string>
#include <vector>
#include <cstdint>

namespace WikiMarkup { namespace Components {

    struct Authority
    {
        std::string user = "";
        std::string password = "";
        std::string host = "";
        uint16_t port = 0;
    };

    struct Url
    {
        std::string scheme;
        Authority authority;
        std::vector <std::string> path; // in segments
        std::string query;
        std::string fragment;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Authority,
    user, password, host, port
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Url,
    scheme, authority, path, query, fragment
)

#endif // COMPONENTS_URL_HPP_INCLUDED
