#include "exportable_table.hpp"

#include "../../conversion.hpp"

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    std::string ExportableTable::toJson() const
    {
        return WikiMarkup::toJson(*this, "Table");
    }
//---------------------------------------------------------------------------------------------------------------------
    void ExportableTable::fromJson(std::string const& str)
    {
        WikiMarkup::fromJson(*this, str);
	}
//---------------------------------------------------------------------------------------------------------------------
    void ExportableTable::fromJson(JSON::ObjectReader const& reader)
    {
        reader.get("data", *this);
    }
//---------------------------------------------------------------------------------------------------------------------
	TableAccessProxy ExportableTable::operator[](std::size_t x)
	{
        return {this, x};
	}
//#####################################################################################################################
	TableAccessProxy::TableAccessProxy(ExportableTable* table, std::size_t x)
		: table_{table}
		, x_{x}
	{
	}
//---------------------------------------------------------------------------------------------------------------------
	TableCell* TableAccessProxy::operator[](std::size_t y)
	{
		if (table_->rows.size() <= y)
			return nullptr;
		if (table_->rows[y].cells.size() <= x_)
			return nullptr;

		return &table_->rows[y].cells[x_];
    }
//#####################################################################################################################
}
}
