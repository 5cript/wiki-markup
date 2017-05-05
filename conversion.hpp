#pragma once

/*
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#   include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"
#
#	include "SimpleJSON/parse/jsd_enum.hpp"
#	include "SimpleJSON/stringify/jss_enum.hpp"
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
#   include "SimpleJSON/stringify/jss_smart_ptr.hpp"
#   include "SimpleJSON/parse/jsd_smart_ptr.hpp"
#endif
*/

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#endif

#include "SimpleJSON/utility/polymorphy.hpp"

#include "SimpleJSON/utility/polymorphy.hpp"
#include "SimpleJSON/utility/object.hpp"

#include <sstream>

namespace WikiMarkup
{
    template <typename T>
    std::string toJson(T const& what, std::string const& name)
    {
        JSON::StringificationOptions options;
        options.strings_are_binary = true;
        JSON::ObjectBuilder builder(options);

        builder.add("name", name);
        builder.add("data", what);

        return builder.get();
    }

    template <typename T>
    void fromJson(T& whereTo, std::string const& json, bool dataEx = false)
    {
        JSON::ParsingOptions options;
        options.strings_are_binary = true;

        auto tree = JSON::parse_json(json);
        JSON::ObjectReader reader(&tree, options);

        if (!dataEx)
            reader.get("", whereTo);
        else
            reader.get("data", whereTo);

        /*
        auto name = reader.get <std::string> ("name");

        if (name != whereTo.getMetaInfo().name)
            throw std::invalid_argument("name in json is not name of component");

        reader.get("data", whereTo);
        */

    }
}
