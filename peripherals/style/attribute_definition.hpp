#ifndef PERIPHERALS_STYLE_ATTRIBUTE_DEFINITION_HPP_INCLUDED
#define PERIPHERALS_STYLE_ATTRIBUTE_DEFINITION_HPP_INCLUDED

#include "value.hpp"
#include "value_types/keyword.hpp"
#include "value_types/numerical.hpp"
#include "value_types/size.hpp"
#include "value_types/string.hpp"
#include "value_types/url.hpp"
#include "value_types/position_size.hpp"
#include "value_types/color.hpp"

#include "mplex/fundamental/null_type.hpp"
#include "mplex/string/string.hpp"
#include "mplex/string/inline_string.hpp"

#include <tuple>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

namespace WikiMarkup { namespace Peripherals  { namespace Style
{
    using namespace ValueTypes;

    template <typename T>
    struct Inheritable
    {
        using type = T;
    };

    template <typename T>
    struct InitialAcceptable
    {
        using type = T;
    };

    template <typename T>
    struct InheritOrInitial
        : public Inheritable <T>, public InitialAcceptable <T>, public Value
    {
        using type = T;
    };

    template <typename T>
    struct Valueifier
    {};

    template <>
    struct Valueifier <Numerical>
    {
        static Numerical* create(std::vector <std::string>::const_iterator begin,
                                 std::vector <std::string>::const_iterator)
        {
            try
            {
                return new Numerical (boost::lexical_cast <double> (*begin));
            }
            catch (boost::bad_lexical_cast const&)
            {
                return nullptr;
            }
        }
    };

    template <>
    struct Valueifier <Color>
    {
        static Color* create(std::vector <std::string>::const_iterator begin,
                             std::vector <std::string>::const_iterator)
        {
            auto maybeColor = tryGetColorFromString(*begin);
            if (!maybeColor)
                return nullptr;

            return new Color(maybeColor.get());
        }
    };

    template <>
    struct Valueifier <Url>
    {
        static Url* create(std::vector <std::string>::const_iterator begin,
                             std::vector <std::string>::const_iterator)
        {
            auto maybeUrl = tryGetUrlFromString(*begin);
            if (!maybeUrl)
                return nullptr;

            return new Url(maybeUrl.get());
        }
    };

    template <typename Name, typename... Parameters>
    struct KnownAttribute
    {
        using name = Name;
        using parameters = std::tuple <Parameters...>;

        bool matches(std::string const& str) const
        {
            return std::string(name::c_str) == str;
        }

        std::vector <std::unique_ptr <Value> > valueify (std::vector <std::string> const& raw)
        {
        }
    };

    using KnownAttributeList = std::tuple <
        // Color Properties
        KnownAttribute <SHORT_STRING("color"), InheritOrInitial <Color>>,
        KnownAttribute <SHORT_STRING("opacity"), InheritOrInitial <Numerical>>,

        // Background Properties
        KnownAttribute <SHORT_STRING("background"),
            Color,
            Url,
            PositionAndSize,
            Keyword <SHORT_STRING("repeat"), SHORT_STRING("repeat-x"), SHORT_STRING("repeat-y"), SHORT_STRING("no-repeat")>, // repeat
            Keyword <SHORT_STRING("padding-box"), SHORT_STRING("border-box"), SHORT_STRING("content-box")>, // origin
            Keyword <SHORT_STRING("border-box"), SHORT_STRING("padding-box"), SHORT_STRING("content-box")>, // background-clip
            Keyword <SHORT_STRING("scroll"), SHORT_STRING("fixed"), SHORT_STRING("local")>, // background-attachment
            InheritOrInitial <mplex::null_t>
        >
    >;

} // namespace Style
} // namespace Peripherals
} // namespace WikiMarkup

#endif // PERIPHERALS_STYLE_ATTRIBUTE_DEFINITION_HPP_INCLUDED
