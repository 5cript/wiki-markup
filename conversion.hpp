#pragma once

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#   include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"
#
#   include "SimpleJSON/parse/jsd_string.hpp"
#   include "SimpleJSON/stringify/jss_string.hpp"
#   include "SimpleJSON/parse/jsd_container.hpp"
#   include "SimpleJSON/stringify/jss_vector.hpp"
#   include "SimpleJSON/parse/jsd_string.hpp"
#   include "SimpleJSON/stringify/jss_string.hpp"
#   include "SimpleJSON/parse/jsd_fundamental.hpp"
#   include "SimpleJSON/stringify/jss_fundamental.hpp"
#   include "SimpleJSON/parse/jsd_map.hpp"
#   include "SimpleJSON/stringify/jss_map.hpp"
#endif

#include "SimpleJSON/utility/polymorphy.hpp"

#include <sstream>

namespace WikiMarkup
{
    struct JsonComponent : public JSON::Stringifiable <JsonComponent>
                         , public JSON::Parsable <JsonComponent>
    {
        std::string name;
        std::string data;
    };

    template <typename T>
    std::string toJson(T const& what, std::string const& name)
    {
        std::stringstream sstr;

        JSON::stringify(sstr, "", what);
        JsonComponent comp;
        comp.name = name;
        comp.data = sstr.str();

        //sstr.clear();

        std::stringstream result;

        JSON::stringify(result, "", comp);

        return result.str();
    }

    template <typename T>
    void fromJson(T& whereTo, std::string const& json)
    {
        JsonComponent comp;
        auto tree = JSON::parse_json("{\"x\":" + json + "}");
        JSON::parse(comp, "x", tree);

        auto tree2 = JSON::parse_json("{\"data\":" + comp.data + "}");
        JSON::parse(whereTo, "data", tree2);

        if (comp.name != whereTo.getMetaInfo().name)
            throw std::invalid_argument("name in json is not name of component");
    }
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::JsonComponent,
    name, data
)
