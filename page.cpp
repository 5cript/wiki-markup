#include "page.hpp"

#include "component_factory.hpp"
#include "constants.hpp"

#include "SimpleJSON/utility/beauty_stream.hpp"
#include "SimpleJSON/parse/jsd_generic_parser.hpp"
#include "SimpleJSON/parse/jsd_string.hpp"
#include "SimpleJSON/utility/array.hpp"
#include "SimpleJSON/utility/object.hpp"

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

#include <iostream>
#include <sstream>

namespace WikiMarkup
{
//####################################################################################
    std::ostream& Page::dumpComponentNames(std::ostream& stream)
    {
        for (auto const& i : components_) {
            stream << i->getMetaInfo().name << " ";
        }

        return stream;
    }
//-----------------------------------------------------------------------------------
    void Page::clear()
    {
        components_.clear();
    }
//-----------------------------------------------------------------------------------
    void Page::appendComponent(Components::IComponent const& component)
    {
        components_.emplace_back(component.clone());
    }
//-----------------------------------------------------------------------------------
    void Page::appendComponent(Components::IComponent* component)
    {
        components_.emplace_back(component);
    }
//-----------------------------------------------------------------------------------
    std::add_lvalue_reference <decltype(Page::components_)>::type Page::getComponents()
    {
        return components_;
    }
//-----------------------------------------------------------------------------------
    std::add_lvalue_reference <decltype(Page::components_) const>::type Page::getComponents() const
    {
        return components_;
    }
//-----------------------------------------------------------------------------------
    std::string Page::toMarkup() const
    {
        std::string result;
        for (auto const& i : components_)
        {
            result += i->toMarkup() + preferredNewline;
        }
        return result;
    }
//-----------------------------------------------------------------------------------
    std::string Page::toJson() const
    {
        std::stringstream json;

        namespace io = boost::iostreams;

        bool first = true;
        json << "[";
        for (auto const& i : components_)
        {
            if (!first)
                json << ",";
            json << i->toJson();
            first = false;
        }
        json << "]";

        io::filtering_streambuf <io::output> buf;
        buf.push(JSON::BeautifiedStreamWrapper());
        buf.push(json);

        std::stringstream result;

        return json.str();
    }
//-----------------------------------------------------------------------------------
    void Page::fromJson(std::string const& json)
    {
        clear();

        auto tree = JSON::parse_json(json);
        JSON::ArrayReader reader(tree);

        JSON::ParsingOptions options;
        options.strings_are_binary = true;
        while (reader)
        {
            auto arrayNode = reader.getNext();
            JSON::ObjectReader object(arrayNode, "", options);

            auto type = object.get <std::string> ("name");
            auto* component = createComponent(type, object);

            if (component == nullptr)
                throw std::runtime_error("json contains component, that has an unknown type: " + type);

            appendComponent(component);
        }
    }
//####################################################################################
}
