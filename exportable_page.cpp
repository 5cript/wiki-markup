#include "exportable_page.hpp"

#include "exp_component_factory.hpp"

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
    void ExportablePage::clear()
    {
        components_.clear();
    }
//-----------------------------------------------------------------------------------
	void ExportablePage::appendComponent(Components::IExportableComponent const& component)
    {
        components_.emplace_back(component.clone());
    }
//-----------------------------------------------------------------------------------
    void ExportablePage::appendComponent(Components::IExportableComponent* component)
    {
        components_.emplace_back(component);
    }
//-----------------------------------------------------------------------------------
    std::add_lvalue_reference <decltype(ExportablePage::components_)>::type ExportablePage::getComponents()
    {
        return components_;
	}
//-----------------------------------------------------------------------------------
	void ExportablePage::setComponents(decltype(ExportablePage::components_) const& components)
	{
		components_ = components;
	}
//-----------------------------------------------------------------------------------
    std::string ExportablePage::toJson() const
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
    void ExportablePage::fromJson(std::string const& json)
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
            auto* component = createExportableComponent(type, object);

            if (component == nullptr)
                throw std::runtime_error("json contains component, that has an unknown type: " + type);

            appendComponent(component);
        }
    }
//####################################################################################
}
