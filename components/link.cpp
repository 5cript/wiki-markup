#include "link.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/link.hpp"

#include "post_processors/link.hpp"

#include "../configuration.hpp"
#include "../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//####################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(Link)
//-----------------------------------------------------------------------------------
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

        auto res = TwistedSpirit::parse <grammar> (mu);
        *this = res.second;
        PostProcessors::postProcessLink(*this);
        return res.first;
    }
//-----------------------------------------------------------------------------------
    MetaInfo Link::getMetaInfoS()
    {
        return {
            "Link",
            false
        };
    }
//-----------------------------------------------------------------------------------
    MetaInfo Link::getMetaInfo() const
    {
        return Link::getMetaInfoS();
    }
//-----------------------------------------------------------------------------------
    Link* Link::clone() const
    {
        return new Link(*this);
    }
//-----------------------------------------------------------------------------------
    bool Link::isImage() const
    {
        if (url.path.empty())
            return false;

        auto fileName = url.path.back();
        auto fromBack = [&fileName](int len)
        {
            return fileName.substr(fileName.length() - len, len);
        };

        auto hasImageExtension = [&fileName, &fromBack]() -> bool
        {
            auto config = Configuration::getInstance().getReadOnly();
            for (auto const& ext : config.imageExtensions)
            {
                if (ext == fromBack(ext.length()))
                    return true;
            }
            return false;
        };

        return prefix == "File" && hasImageExtension();
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
