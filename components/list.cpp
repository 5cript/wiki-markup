#include "list.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "parsers/list.hpp"

#include "post_processors/list.hpp"

#include "../configuration.hpp"

#include <sstream>

namespace WikiMarkup { namespace Components {
//#####################################################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(List)
//---------------------------------------------------------------------------------------------------------------------
    std::string List::toMarkup()
    {
        std::stringstream sstr;

        auto lineEnd = Configuration::getInstance().getReadOnly().lineEndings.toString();

        std::function <void(std::string, PrimalList*)> subPrintList =
        [&, this](std::string prefix, PrimalList* list)
        {
            for (auto const& i : list->elements)
            {
                PrimalList* primal = dynamic_cast <PrimalList*> (i.get());
                if (primal != nullptr)
                {
                    subPrintList(prefix + ListChars[static_cast <std::size_t> (primal->type)], primal);
                }
                else
                {
                    auto* line = dynamic_cast <ListTextLine*> (i.get());
                    sstr << prefix << ' ' << line->data << lineEnd;
                }
            }
        };

        std::string prefix;
        prefix.push_back(ListChars[static_cast <std::size_t> (list.type)]);
        subPrintList(prefix, &list);

        return sstr.str();
    }
//---------------------------------------------------------------------------------------------------------------------
    ParsingResult List::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(list_grammar);

        auto res = TwistedSpirit::parse <grammar> (mu);

        if (res.first != ParsingResult::FAIL)
            this->list = PostProcessors::postProcessList(res.second);
        return res.first;
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo List::getMetaInfo() const
    {
        return List::getMetaInfoS();
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo List::getMetaInfoS()
    {
        return {
            "List",
            true
        };
    }
//---------------------------------------------------------------------------------------------------------------------
    List* List::clone() const
    {
        return new List(*this);
    }
//#####################################################################################################################
} // namespace Components
} // namespace WikiMarkup
