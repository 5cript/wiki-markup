#include "url.hpp"

#include "../../../parser/qi_common/parse.hpp"

#include "../../parsers/style/url.hpp"

namespace WikiMarkup { namespace Peripherals { namespace Style { namespace ValueTypes
{
//####################################################################################
    Url::Url(std::string value)
        : value(std::move(value))
    {

    }
//####################################################################################
    boost::optional <Url> tryGetUrlFromString(std::string const& str)
    {
        using namespace WikiMarkup::Peripherals::Style::Parser;

        TYPEDEF_GRAMMAR(url_grammar);
        auto maybeUrl = parse<grammar>(str);

        if (maybeUrl.first == ParsingResult::FULL_SUCCESS)
            return boost::optional <Url> (maybeUrl.second);

        return boost::none;
    }
//####################################################################################
} // namespace ValueTypes
} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup
