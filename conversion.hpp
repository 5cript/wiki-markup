#pragma once

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.h"
#   include "SimpleJSON/parse/jsd_convenience.h"
#   include "SimpleJSON/stringify/jss.h"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif

#include <sstream>

namespace WikiMarkup
{
    struct JsonComponent
    {
        std::string name;
        std::string data;
    };

    template <typename T>
    std::string toJson(T const& what, std::string const& name)
    {
        std::stringstream sstr;

        JSON::try_stringify(sstr, "", what);
        JsonComponent <T> comp;
        comp.name = name;
        comp.data = sstr.str();

        sstr.clear();

        JSON::try_stringify(sstr, "", comp);

        return sstr.str();
    }

    template <typename T>
    void fromJson(T& whereTo, std::string const& json)
    {
        JsonComponent comp;
        auto tree = JSON::parse_json("{\"x\":" + json + "}");
        JSON::try_parse(comp, "x", tree);

        auto tree2 = JSON::parse_json("{\"data\":" + comp.data + "}");
        JSON::try_parse(whereTo, "data", tree2);

        if (comp.name != whereTo.getMetaInfo().name)
            throw std::invalid_argument("name in json is not name of component");
    }
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::JsonComponent,
    name, data
)
