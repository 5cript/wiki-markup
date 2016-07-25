#include "table.hpp"

#include <algorithm>
#include <cctype>

namespace WikiMarkup { namespace Components { namespace PostProcessors {

    void postProcessTable(Table& table)
    {
        table.rows.erase(std::remove_if(std::begin(table.rows), std::end(table.rows), [](decltype(table.rows)::value_type const& row) {
            return row.cells.empty();
        }), std::end(table.rows));

        for (auto& row : table.rows) {
            for (auto& cell : row.cells) {
                while (!cell.data.empty() && std::isblank(cell.data.back()))
                    cell.data.pop_back();
            }
        }
    }

} // namespace PostProcessors
} // namespace Components
} // namespace WikiMarkup
