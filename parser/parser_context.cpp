#include "parser_context.hpp"

#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace WikiMarkup
{
//####################################################################################
    DLL_EXPORT ParserContext::ParserContext(std::string page)
        : page_{std::move(page)}
        , position_{0}
        , lines_{}
        , tokens_{}
    {
        tokenize();
        splitLines();
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT void ParserContext::tokenize()
    {
        // approximate. speeds up code.
        tokens_.reserve(page_.length() / 8);

        std::string tokenData;
        auto begin = page_.cbegin();
        for (auto i = page_.cbegin(), end = page_.cend(); i < end;) {
            boost::optional <Token> tok = extractToken(begin, i, end);
            if (!tok)
                throw std::runtime_error("unexpected unclassifiable token type");
            tokens_.push_back(tok.get());
        }
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT void ParserContext::splitLines()
    {
        Line line;
        line.start = 0;
        for (auto i = std::begin(page_), end = std::end(page_); i != end; ++i) {
            if (*i == '\n') {
                if (i + 1 != end && *(i + 1) == '\r')
                    ++i;

                line.end = i - std::begin(page_) + 1;
                lines_.push_back(line);
                line.data.clear();
                line.start = line.end;
            } else if (*i == '\r') {
                if (i + 1 != end && *(i + 1) == '\n')
                    ++i;

                line.end = i - std::begin(page_) + 1;
                lines_.push_back(line);
                line.data.clear();
                line.start = line.end;
            } else {
                line.data.push_back(*i);
            }
        }

        line.end = std::end(page_) - std::begin(page_);
        lines_.push_back(line);
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT char ParserContext::get(bool peek) const noexcept
    {
        if (!hasMoreToRead())
            return '\0';

        char c = page_[position_]; // cannot throw because its checked.
        if (!peek)
            ++position_;
        return c;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT boost::optional <Token> ParserContext::getToken(bool peek) const
    {
        if (!hasMoreToRead())
            return boost::none;

        for (auto const& i : tokens_) {
            if (i.getStartPosition() <= position_ && i.getEndPosition() > position_) {
                if (!peek)
                    position_ = i.getEndPosition();
                return i;
            }
        }
        return boost::none;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT boost::optional <std::string> ParserContext::getLine(bool peek) const
    {
        if (!hasMoreToRead())
            return boost::none;

        for (auto const& i : lines_) {
            if (i.start <= position_ && i.end > position_) {
                if (!peek)
                    position_ = i.end;
                return i.data;
            }
        }

        return boost::none;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT void ParserContext::setCursorToEnd()
    {
        position_ = page_.length();
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT bool ParserContext::isStartOfLine() const
    {
        auto iter = std::find_if(std::begin(lines_), std::end(lines_), [this](Line const& l) {
            return position_ == l.start;
        });
        return iter != std::end(lines_);
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT bool ParserContext::hasMoreToRead() const noexcept
    {
        return position_ < page_.length();
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT ParserContext::position_type ParserContext::getPosition() const noexcept
    {
        return position_;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT void ParserContext::setPosition(position_type position) noexcept
    {
        position_ = position;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT void ParserContext::forwardPosition(position_type amount) noexcept
    {
        position_ += amount;

        // set to end. A position that is past-the-end is not valid state.
        if (!hasMoreToRead())
            position_ = page_.length();
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT std::string ParserContext::getSlice() const
    {
        return page_.substr(position_, page_.length() - position_);
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT ParserContext& ParserContext::operator++() noexcept
    {
        ++position_;
        return *this;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT ParserContext ParserContext::operator++(int) noexcept
    {
        position_++;
        return *this;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT ParserContext& ParserContext::operator--() noexcept
    {
        --position_;
        return *this;
    }
//-----------------------------------------------------------------------------------
    DLL_EXPORT ParserContext ParserContext::operator--(int) noexcept
    {
        position_--;
        return *this;
    }
//####################################################################################
}
