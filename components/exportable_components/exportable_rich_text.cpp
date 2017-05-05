#include "exportable_rich_text.hpp"

#include "../../conversion.hpp"
#include "SimpleJSON/utility/beauty_stream.hpp"
#include "SimpleJSON/utility/array.hpp"

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

#include "../exportable_components_jspoly.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableRichText::toJson() const
    {
        std::stringstream json;

        namespace io = boost::iostreams;

        bool first = true;
        json << "[";
        for (auto const& i : subelements)
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

        return json.str();
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableRichText::fromJson(std::string const& str)
    {
        throw std::runtime_error ("IMPLEMENT ME");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableRichText::fromJson(JSON::ObjectReader const& reader)
    {
        throw std::runtime_error ("IMPLEMENT ME");
    }
//---------------------------------------------------------------------------------------------------------------------
    ExportableRichText* ExportableRichText::clone() const
    {
        return new ExportableRichText(*this);
    }
//#####################################################################################################################
}
}
