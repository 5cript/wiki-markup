#include "link.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/link.hpp"

#include "post_processors/link.hpp"

namespace WikiMarkup { namespace Components
{
//####################################################################################
    std::string Link::toMarkup()
    {
        std::stringstream sstr;

        std::cout << url.scheme << "\n";
        std::cout << url.authority.host << "\n";

        auto appendAttributes = [&, this]() {
            if (!attributes.empty())
            {
                sstr << '|';
                sstr << attributes.front();
            }
        };

        auto printRedirect = [&, this]() {
            if (redirect)
                sstr << "#REDIRECT ";
        };

        if (internal)
        {
            // anchor detection is not useful the way it was before.
            // no parsing, therefor no generation.

            printRedirect();

            sstr << "[[" << prefix;

            if (colon)
            {
                sstr << ':';
                sstr << localPart;
            }

            appendAttributes();

            sstr << "]]";
        }
        else if (!implicit)
        {
            printRedirect();

            sstr << '[';
            sstr << url.toString();

            appendAttributes();

            sstr << ']';
        }
        else
        {
            sstr << url.toString();
        }

        return sstr.str();
    }
//-----------------------------------------------------------------------------------
    ParsingResult Link::fromMarkup(std::string const& mu)
    {
        using namespace TwistedSpirit;
        using namespace WikiMarkup::Components::Parser;

        TYPEDEF_GRAMMAR(link_grammar);

        auto res = parse <grammar> (mu);
        *this = res.second;
        PostProcessors::postProcessLink(*this);
        return res.first;
    }
//-----------------------------------------------------------------------------------
    MetaInfo Link::getMetaInfo() const
    {
        return {
            "Link",
            false
        };
    }
//-----------------------------------------------------------------------------------
    Link* Link::clone() const
    {
        return new Link(*this);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
