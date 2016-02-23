#ifndef COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED

#include "../comments.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct comment_grammar : qi::grammar <Iterator, CommentText(), qi::locals <CommentText>>
    {
        using grammar_result = CommentText;

        comment_grammar() : comment_grammar::base_type(main, "comments")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			comment.name("comment");
			//no_comment.name("no_comment");

			comment %=
                    lit("<!--")
                >> *(qi::char_ - lit("-->"))
                >> -lit("-->")
			;

			// no_comment %= +(qi::char_ - lit("<!--"));

			main =
                comment             [at_c <0> (_val) = qi::_1]
			;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> comment;
        // qi::rule <Iterator, std::string()> no_comment;
        qi::rule <Iterator, grammar_result(), qi::locals <CommentText>> main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
