#pragma once

#include "SimpleJSON/stringify/jss_smart_ptr.hpp"
#include "SimpleJSON/parse/jsd_smart_ptr.hpp"

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, sutil::value_ptr <T> const& value, JSON::StringificationOptions const& options = {})
    {
        return internal::stringify_smart_ptr(stream, name, value, options);
    }

    template <typename T>
    void parse(sutil::value_ptr <T>& value, std::string const& name, JSON::PropertyTree const& object, JSON::ParsingOptions const& options = {})
    {
        return internal::parse_smart_ptr(value, name, object, options);
    }
}
