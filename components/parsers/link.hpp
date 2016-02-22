#ifndef COMPONENTS_PARSERS_LINKS_HPP_INCLUDED
#define COMPONENTS_PARSERS_LINKS_HPP_INCLUDED

#include "../link.hpp"

#include "../../parser/qi_common/parser_core.hpp"
#include "../../parser/qi_common/basic.hpp"

#include "url.hpp"

#include <string>
#include <vector>

namespace WikiMarkup { namespace Components { namespace Parser
{

template GRAMMAR_TEMPLATE_SIGNATURE
    struct link_grammar : qi::grammar <Iterator, Link(), qi::locals <bool>>
    {
        using grammar_result = Link;

        link_grammar() : link_grammar::base_type(main, "authority")
        {
            using namespace common_usings;
            using namespace Rules;

            INSTALL_DEBUG_HANDLER;

            internalLinkBegin = qi::lit("[[");
            internalLinkEnd = qi::lit("]]");

            externalLinkBegin = qi::char_("[");
            externalLinkEnd = qi::char_("]");

            preColon =
               +(qi::char_ - qi::char_(":|]"))
            ;

            postColon =
               +(qi::char_ - qi::char_("|]"))
            ;

            attribute =
               +(qi::char_ - qi::char_("|]"))
            ;

            internalLink =
                    internalLinkBegin           [at_c <0> (_val) = true]
                >> *space
                >> -(
                            preColon            [at_c <4> (_val) = qi::_1]
                        >>  qi::char_(':')      [at_c <2> (_val) = true]
                    )
                >>  postColon                   [at_c <5> (_val) = qi::_1]
                >> *( // attributes / pipe
                            qi::char_('|')
                        >>  attribute           [phoenix::push_back(at_c <6> (_val), qi::_1)]
                    )
                >>  internalLinkEnd
            ;

            externalLink =
                    externalLinkBegin           [at_c <0> (_val) = false]
                >>  url                         [at_c <7> (_val) = qi::_1]
                >> !qi::char_('|')
                >> -(
                            +space
                        >>  attribute           [phoenix::push_back(at_c <6> (_val), qi::_1)]
                    )
                >>  externalLinkEnd
            ;

            implicitLink =
                    url                         [at_c <7> (_val) = qi::_1]
                >>  eps
                    [
                        at_c <0> (_val) = false,
                        at_c <1> (_val) = true,
                        at_c <2> (_val) = false,
                        at_c <3> (_val) = false
                    ]
            ;

            main =
                   -(
                            qi::lit("#REDIRECT")    [_a = true]
                        >> *space
                    )
                >>  (
                            externalLink
                        |   internalLink
                        |   implicitLink)           [_val = qi::_1]
                >>  eps                             [at_c <8> (_val) = _a]
            ;
        };

        // Rules
        qi::rule <Iterator, grammar_result(), qi::locals <bool>> main;

        qi::rule <Iterator> internalLinkBegin;
        qi::rule <Iterator> internalLinkEnd;

        qi::rule <Iterator> externalLinkBegin;
        qi::rule <Iterator> externalLinkEnd;

        qi::rule <Iterator, Link()> internalLink;
        qi::rule <Iterator, Link()> externalLink;
        qi::rule <Iterator, Link()> implicitLink;

        qi::rule <Iterator, std::string()> preColon;
        qi::rule <Iterator, std::string()> postColon;
        qi::rule <Iterator, std::string()> attribute;

        // Grammars
        url_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD url;
    };

} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_LINKS_HPP_INCLUDED
