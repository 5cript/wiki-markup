#pragma once

#include "../html.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"
#include "twisted-spirit/grammars/unescaped_string.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct raw_html_grammar : qi::grammar <Iterator, RawHtmlTreeNode(), qi::locals <char>>
    {
        using grammar_result = RawHtmlTreeNode;

        raw_html_grammar() : raw_html_grammar::base_type(main, "html")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;
			INSTALL_DEBUG_HANDLER;

			start.name("start-tag");
			name.name("name");
			param.name("parameter");
			parameters.name("parameters");
			end.name("end-tag");
			content.name("content");
			node.name("node");

            name =
                +qi::alnum
            ;

            param =
                    name                                [at_c <0> (_val) = qi::_1]
                >>  qi::char_('=')
                >>  unescaped                           [at_c <1> (_val) = qi::_1]
            ;

			parameters =
               *(
                       +space
                    >>  param
                )
			;

			start =
                    qi::char_('<')
                >> !qi::char_('/')
                >>  name                                [at_c <0> (_val) = qi::_1]
                >>  parameters                          [at_c <1> (_val) = qi::_1]
			;

			end =
                    qi::lit("</")
                >>  qi::string(_r1)
                >>  qi::char_('>')
			;

            content =
                    node                                [at_c <1> (_val) = qi::_1]
                |  +(qi::char_ - qi::char_('<'))        [phoenix::push_back(at_c <0> (_val), qi::_1)]
            ;

			node =
                    start                               [_val = qi::_1]
                >> *space
                >>  (
                            qi::lit("/>")               [at_c <3> (_val) = false]
                        |   (
                                    qi::char_('>')      [at_c <3> (_val) = true]
                                >> *content             [phoenix::push_back(at_c <2> (_val), qi::_1)]
                                >>  end(at_c <0> (_val))
                            )
                    )
			;

			main =
                node
			;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule<Iterator, std::string()> name;
        qi::rule<Iterator, std::pair<std::string, std::string>()> param;
        qi::rule<Iterator, RawHtmlTreeNode::parameters_type()> parameters;
        qi::rule<Iterator, RawHtmlTreeNode()> node;
        qi::rule<Iterator, RawHtmlTreeNode::content_or_node()> content;
        qi::rule<Iterator, RawHtmlTreeNode()> start;
        qi::rule<Iterator, void(std::string)> end;
        qi::rule <Iterator, grammar_result(), qi::locals <char>> main;

        // Grammars
        unescaped_string_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD unescaped;
    };
} // Parser
} // Components
} // WikiMarkup
