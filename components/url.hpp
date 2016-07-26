#ifndef COMPONENTS_URL_HPP_INCLUDED
#define COMPONENTS_URL_HPP_INCLUDED

#include "adaption.hpp"
#include "../json_introspection.hpp"

#include <string>
#include <vector>
#include <cstdint>

namespace WikiMarkup { namespace Components {

    struct Authority : public JSON::Stringifiable <Authority>
                     , public JSON::Parsable <Authority>
    {
        std::string user = "";
        std::string password = "";
        std::string host = "";
		uint16_t port = 0;
    };

    struct Url : public JSON::Stringifiable <Url>
               , public JSON::Parsable <Url>
    {
        std::string scheme;
        Authority authority;
        std::vector <std::string> path; // in segments
        std::string query;
        std::string fragment;

        std::string toString() const;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::Authority,
	(std::string, user)
	(std::string, password)
	(std::string, host)
	(uint16_t, port)
)

BOOST_FUSION_ADAPT_STRUCT
(
	WikiMarkup::Components::Url,
	(std::string, scheme)
	(WikiMarkup::Components::Authority, authority)
	(std::vector <std::string>, path)
	(std::string, query)
	(std::string, fragment)
)

#endif // COMPONENTS_URL_HPP_INCLUDED
