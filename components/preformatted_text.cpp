#include "preformatted_text.hpp"
#include "../configuration.hpp"

#include <cctype>
#include <sstream>

namespace WikiMarkup { namespace Components {
//####################################################################################
        std::string PreformattedText::toMarkup()
        {
            std::string result;
            for (auto const& i : lines) {
                result += i.space + i.data + Configuration::getInstance().getReadOnly().lineEndings;
            }
            return result;
        }
//-----------------------------------------------------------------------------------
        ParsingResult PreformattedText::fromMarkup(std::string const& mu)
        {
            auto singleLine = [](std::string const& line, PreformattedLine& prefLine) -> ParsingResult
            {
                if (line.empty() || !std::isspace(line.front()))
                {
                    return ParsingResult::FAIL;
                }

                auto i = std::begin(line);
                for (auto end = std::end(line); i != end; ++i)
                {
                    if (std::isspace(*i))
                        prefLine.space.push_back(*i);
                    else
                        break;
                }
                prefLine.data = {i, std::end(line)};

                return ParsingResult::FULL_SUCCESS;
            };

            std::stringstream sstr (mu);
            sstr.seekg(0);

            std::string line;
            while (std::getline(sstr, line)) {
                PreformattedLine pline;
                auto result = singleLine(line, pline);
                if (result != ParsingResult::FAIL)
                    lines.push_back(pline);
                else
                    return ParsingResult::FAIL;
            }

            return ParsingResult::FULL_SUCCESS;
        }
//-----------------------------------------------------------------------------------
        std::string PreformattedText::getName() const
        {
            return "Preformatted_Text";
        }
//-----------------------------------------------------------------------------------
        PreformattedText* PreformattedText::clone() const
        {
            return new PreformattedText(*this);
        }
//-----------------------------------------------------------------------------------
        std::string PreformattedText::getRaw() const
        {
            std::string joined;
            for (auto const& i : lines) {
                joined += i.space + i.data + Configuration::getInstance().getReadOnly().lineEndings;
            }
            return joined;
        }
//####################################################################################
} // namespace Components
} // namespace WikiMarkup
