#include "parser_context.hpp"

#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace WikiMarkup
{
//####################################################################################
    ParserContext::ParserContext(std::string page)
        : page_{std::move(page)}
        , position_{0}
        , lines_{}
        , tokens_{}
    {
        tokenize();
        splitLines();
    }
//-----------------------------------------------------------------------------------
    void ParserContext::tokenize()
    {
        // approximate. speeds up code.
        tokens_.reserve(page_.length() / 8);

        std::string tokenData;
        auto begin = std::cbegin(page_);
        for (auto i = std::cbegin(page_), end = std::cend(page_); i < end;) {
            boost::optional <Token> tok = extractToken(begin, i, end);
            if (!tok)
                throw std::runtime_error("unexpected unclassifiable token type");
            tokens_.push_back(tok.get());
        }
    }
//-----------------------------------------------------------------------------------
    void ParserContext::splitLines()
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
    char ParserContext::get(bool peek) const
    {
        if (!hasMoreToRead())
            return '\0';

        char c = page_[position_];
        if (!peek)
            ++position_;
        return c;
    }
//-----------------------------------------------------------------------------------
    boost::optional <Token> ParserContext::getToken(bool peek) const
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
    boost::optional <std::string> ParserContext::getLine(bool peek) const
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
    bool ParserContext::isStartOfLine() const
    {
        auto iter = std::find_if(std::begin(lines_), std::end(lines_), [this](Line const& l) {
            return position_ == l.start;
        });
        return iter != std::end(lines_);
    }
//-----------------------------------------------------------------------------------
    bool ParserContext::hasMoreToRead() const
    {
        return position_ < page_.length();
    }
//-----------------------------------------------------------------------------------
    std::size_t ParserContext::getPosition() const
    {
        return position_;
    }
//-----------------------------------------------------------------------------------
    void ParserContext::setPosition(std::size_t position)
    {
        position_ = position;
    }
//-----------------------------------------------------------------------------------
    ParserContext& ParserContext::operator++()
    {
        ++position_;
        return *this;
    }
//-----------------------------------------------------------------------------------
    ParserContext ParserContext::operator++(int)
    {
        position_++;
        return *this;
    }
//-----------------------------------------------------------------------------------
    ParserContext& ParserContext::operator--()
    {
        --position_;
        return *this;
    }
//-----------------------------------------------------------------------------------
    ParserContext ParserContext::operator--(int)
    {
        position_--;
        return *this;
    }
//####################################################################################
}
