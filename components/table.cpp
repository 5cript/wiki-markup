#include "table.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/table.hpp"
#include "post_processors/table.hpp"

#include "../configuration.hpp"

#include "../conversion.hpp"

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
            sstr << lineEnd;
        }

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
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(table_grammar);

        auto res = TwistedSpirit::parse <grammar> (mu);
        if (res.first != ParsingResult::FAIL) {
            *this = res.second;
            postProcessTable(*this);
        }
        return res.first;
    }
//-----------------------------------------------------------------------------------
    std::string Table::toJson() const
    {
        return WikiMarkup::toJson(*this, getMetaInfo().name);
    }
//-----------------------------------------------------------------------------------
    void Table::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
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
    Table stripHeaders(Table const& table)
    {
        Table stripped = table;
        stripped.rows.clear();

        int scanOffset = 0;
        if (!table.rows.empty() && !table.rows.front().cells.empty() && table.rows.front().cells.front().isHeaderCell)
            scanOffset = 1;

        for (auto i = std::begin(table.rows) + scanOffset, end = std::end(table.rows); i < end; ++i)
        {
            int copyOffset = 0;
            if (!i->cells.empty() && i->cells.front().isHeaderCell)
                copyOffset = 1;

            std::vector <TableCell> cells;
            for (auto c = std::begin(i->cells) + copyOffset, endCells = std::end(i->cells); c < endCells; ++c)
                cells.push_back(*c);

            TableRow r = *i;
            r.cells = cells;
            stripped.rows.push_back(r);
        }

        return stripped;
    }
//-----------------------------------------------------------------------------------
    std::vector <TableCell> getHorizontalHeaders(Table const& table)
    {
        if (!table.rows.empty())
            return table.rows.front().cells;
        return {};
    }
//-----------------------------------------------------------------------------------
    std::vector <TableCell> getVerticalHeaders(Table const& table, bool noOverlap)
    {
        std::vector <TableCell> cells;

        for (auto const& i : table.rows)
            if (!i.cells.empty() && i.cells.front().isHeaderCell && !noOverlap)
                cells.push_back(i.cells.front());
            else if (!i.cells.empty() && i.cells.front().isHeaderCell && noOverlap)
                noOverlap = false;

        return cells;
    }
//-----------------------------------------------------------------------------------
} // namespace Components
} // namespace WikiMarkup
