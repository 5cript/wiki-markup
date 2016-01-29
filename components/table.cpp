#include "table.hpp"

#include "parsers/parse.hpp"
#include "parsers/table.hpp"
#include "post_processors/table.hpp"

#include "../configuration.hpp"

#include <sstream>

namespace WikiMarkup { namespace Components {
//####################################################################################
    std::string Table::toMarkup()
    {
        std::stringstream sstr;

        auto lineEnd = Configuration::getInstance().getReadOnly().lineEndings.toString();

        auto printAttributes = [&](std::pair <std::string, std::string> const& attr)
        {
            sstr << ' ' << attr.first << "=\"" << attr.second << "\"";
        };

        sstr << "{|";

        // Attributes.
        for (auto const& i : attributes)
            printAttributes(i);

        sstr << lineEnd;

        // Caption
        if (!caption.data.empty())
        {
            // Attributes
            sstr << "|+";

            for (auto const& i : caption.attributes)
                printAttributes(i);

            if (!caption.attributes.empty())
                sstr << "|''" << caption.data << "''";
            else
                sstr << ' ' << caption.data;
        }
        sstr << lineEnd;

        // Rows
        for (auto const& i : rows)
        {
            sstr << "|-";

            // Row Attributes
            for (auto const& a : i.attributes)
                printAttributes(a);

            sstr << lineEnd;

            for (auto const& cell : i.cells)
            {
                if (cell.isHeaderCell)
                    sstr << '!';
                else
                    sstr << '|';

                for (auto const& a : cell.attributes)
                    printAttributes(a);

                if (!cell.attributes.empty())
                    sstr << " |";

                sstr << ' ' << cell.data << lineEnd;
            }
        }

        sstr << "|}";

        return sstr.str();
    }
//-----------------------------------------------------------------------------------
    ParsingResult Table::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace WikiMarkup::Components::PostProcessors;

        TYPEDEF_GRAMMAR(table_grammar);

        auto res = parse <grammar> (mu);
        if (res.first != ParsingResult::FAIL) {
            *this = res.second;
            postProcessTable(*this);
        }
        return res.first;
    }
//-----------------------------------------------------------------------------------
    MetaInfo Table::getMetaInfo() const
    {
        return {
            "Table",
            false
        };
    }
//-----------------------------------------------------------------------------------
    Table* Table::clone() const
    {
        return new Table(*this);
    }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
