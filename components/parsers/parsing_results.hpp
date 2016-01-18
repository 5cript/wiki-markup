#ifndef COMPONENTS_PARSING_RESULTS_HPP_INCLUDED
#define COMPONENTS_PARSING_RESULTS_HPP_INCLUDED

namespace WikiMarkup { namespace Components {

    enum class ParsingResult
    {
        FULL_SUCCESS,
        PARTIAL,
        FAIL
    };

} // namespace Components
} // namespace WikiMarkup

#endif // COMPONENTS_PARSING_RESULTS_HPP_INCLUDED
