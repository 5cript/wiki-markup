#ifndef COMPONENTS_PARSING_RESULTS_HPP_INCLUDED
#define COMPONENTS_PARSING_RESULTS_HPP_INCLUDED

namespace WikiMarkup {

    enum class ParsingResult
    {
        FAIL = -3,
        FULL_SUCCESS = -2,
        PARTIAL = -1
    };

} // namespace WikiMarkup

#endif // COMPONENTS_PARSING_RESULTS_HPP_INCLUDED
