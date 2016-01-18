#include "token_classification.hpp"

#include "helpers.hpp"

namespace WikiMarkup
{
//####################################################################################
    const std::string operatorTokens[] = {
        "...", "<<=", ">>=", "!=", "%=", "##",
        "&&", "&=", "*=", "++", "+=", "--", "-=", "->", "/=", "<<", "<=", "==", ">=",
        ">>", "^=", "|=", "||", "%", "&", "(", ")",
        "<", "=", ">", "[", "]", "^", "{", "|", "}", "#"
        // no operators:
        // ? , . * + - / : ; ! ~
    };
//####################################################################################
    std::string extractOperatorToken(std::string::const_iterator begin, std::string::const_iterator end)
    {
        if (begin >= end)
			return {};

		auto cur = begin;
		for (auto const& i : operatorTokens)
		{
			bool fullmatch = true;
			cur = begin;
			auto j = std::begin(i);
			for (; j != std::end(i) && cur != end; ++j)
			{
				if (*cur != *j)
				{
					fullmatch = false;
					break;
				}
				++cur;
			}
			if (cur == end && j != std::end(i))
				continue;
			if (fullmatch)
			{
				begin = cur - 1;
				return i;
			}
		}
		return "";
    }
//------------------------------------------------------------------------------------
    std::string extractTextToken(std::string::const_iterator begin, std::string::const_iterator end)
    {
        if (begin >= end)
            return {};

        std::string tokenData;

        for (;begin != end && !isWhitespace(*begin) && extractOperatorToken(begin, end).empty(); ++begin)
            tokenData.push_back(*begin);

        return tokenData;
    }
//------------------------------------------------------------------------------------
    std::string extractWhitespaceToken(std::string::const_iterator begin, std::string::const_iterator end)
    {
        if (begin >= end)
            return {};

        std::string tokenData;

        for (;begin != end && isWhitespace(*begin); ++begin)
            tokenData.push_back(*begin);

        return tokenData;
    }
//####################################################################################
}
