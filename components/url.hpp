#ifndef COMPONENTS_URL_HPP_INCLUDED
#define COMPONENTS_URL_HPP_INCLUDED

#include "adaption.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    struct Url
    {
        std::string scheme;
        std::string domain;
        std::string port;
        std::string path;
        std::string query;
        std::string fragment;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Url,
    (BOOST_FUSION_ADAPT_AUTO, scheme)
    (BOOST_FUSION_ADAPT_AUTO, domain)
    (BOOST_FUSION_ADAPT_AUTO, port)
    (BOOST_FUSION_ADAPT_AUTO, path)
    (BOOST_FUSION_ADAPT_AUTO, query)
    (BOOST_FUSION_ADAPT_AUTO, fragment)
)

#endif // COMPONENTS_URL_HPP_INCLUDED
