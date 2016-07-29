#include "page.hpp"

#include "SimpleJSON/utility/beauty_stream.hpp"

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
    std::add_lvalue_reference <decltype(Page::components_)>::type Page::getComponents()
    {
        return components_;
    }
//-----------------------------------------------------------------------------------
    std::string Page::toMarkup() const
    {
        std::string result;
        for (auto const& i : components_)
        {
            result += i->toMarkup();
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
//####################################################################################
}
