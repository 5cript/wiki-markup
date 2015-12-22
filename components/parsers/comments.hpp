#ifndef COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
#define COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED

#include "../comments.hpp"

#include "parser_core.hpp"
#include "basic.hpp"

namespace WikiMarkup { namespace Components { namespace Parser
{
    template GRAMMAR_TEMPLATE_SIGNATURE
    struct comment_grammar : qi::grammar <Iterator, std::vector <CommentText>(), qi::locals <CommentText>>
    {
        using grammar_result = std::vector <CommentText>;

        comment_grammar() : comment_grammar::base_type(main, "comments")
        {
            using namespace common_usings;
            using namespace Rules;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			comment.name("comment");
			no_comment.name("no_comment");

			comment %=
                    lit("<!--")
                >> *(qi::char_ - lit("-->"))
                >> -lit("-->")
			;

			no_comment %= +(qi::char_ - lit("<!--"));

            // comment or no comment, that is the question :D
			main =
               *(
                    (
                        (
                            comment
                            [
                                at_c <1> (_a) = true,
                                at_c <0> (_a) = qi::_1
                            ]
                        )
                        |
                        (
                            no_comment
                            [
                                at_c <1> (_a) = false,
                                at_c <0> (_a) = qi::_1
                            ]
                        )
                    )
                    >>  eps [phoenix::push_back(_val, _a)]
                )
			;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, std::string()> comment;
        qi::rule <Iterator, std::string()> no_comment;
        qi::rule <Iterator, grammar_result(), qi::locals <CommentText>> main;
    };
} // Parser
} // Components
} // WikiMarkup

#endif // COMPONENTS_PARSERS_COMMENTS_HPP_INCLUDED
