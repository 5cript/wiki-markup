#ifndef PARSER_TABLE_HPP_INCLUDED
#define PARSER_TABLE_HPP_INCLUDED

#include "../components/holders/table.hpp"

namespace WikiMarkup { namespace Parser {

    Components::Holders::Table parseTable(std::string const& table);

} // Parser
} // WikiMarkup

#endif // PARSER_TABLE_HPP_INCLUDED
