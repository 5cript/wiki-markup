#include "html.hpp"

#include "parsers/raw_html.hpp"
#include "../parser/page_parser.hpp"
#include "twisted-spirit/core/parse.hpp"
#include "../promote_component.hpp"

#include <iostream>

namespace WikiMarkup { namespace Components
{
//#####################################################################################################################
    WMC_EXPORTABLE_DELEGATION_SOURCE(Html)
//---------------------------------------------------------------------------------------------------------------------
    Html::Html(HtmlTreeNode const& tree)
        : ExportableHtml{tree}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    std::string Html::toMarkup()
    {
        std::function <std::string(HtmlTreeNode const& node)> stringifyNode;
        stringifyNode = [&stringifyNode](HtmlTreeNode const& node) {
            std::string res = "<";
            res += node.name;
            for (auto const& i : node.parameters)
            {
                res += " ";
                res += i.first;
                res += "=\"";
                res += i.second;
                res += "\"";
            }
            if (!node.has_content)
                res += "/";
            res += ">";
            for (auto const& i : node.children)
            {
                std::unique_ptr <IComponent> promoted (promoteComponent(i.get()));
                res += promoted->toMarkup();
                /*
                if (i.second)
                    res += stringifyNode(i.second.get());
                else
                    res += i.first;
                */
            }
            if (node.has_content)
            {
                res += "</";
                res += node.name;
                res += ">";
            }
            return res;
        };
        return stringifyNode(tree);
    }
//---------------------------------------------------------------------------------------------------------------------
    ParsingResult Html::fromMarkup(std::string const& mu)
    {
        using namespace WikiMarkup::Components::Parser;
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(raw_html_grammar);

        std::function <HtmlTreeNode(RawHtmlTreeNode const&)> convertNode;
        convertNode = [&convertNode](RawHtmlTreeNode const& node) -> HtmlTreeNode
        {
            HtmlTreeNode result;
            result.name = node.name;
            result.parameters = node.parameters;
            result.has_content = node.has_content;

            for (auto const& child : node.children)
            {
                // is html child:
                if (child.second)
                {
                    result.children.emplace_back(new Html(convertNode(child.second.get())));
                }
                else
                {
                    PageParser parser{child.first};
                    parser.parse();
                    auto page = parser.getPage();
                    auto& comps = page.getComponents();
                    for (auto const& i : comps)
                    {
                        result.children.emplace_back(i->clone());
                    }
                }
            }
            return result;
        };

        auto res = TwistedSpirit::parse <grammar> (mu);
        if (res.first != ParsingResult::FAIL)
        {
            tree = convertNode(res.second);
        }

        return res.first;
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo Html::getMetaInfo() const
    {
        return Html::getMetaInfoS();
    }
//---------------------------------------------------------------------------------------------------------------------
    MetaInfo Html::getMetaInfoS()
    {
        return {
            "Html",
            false
        };
    }
//---------------------------------------------------------------------------------------------------------------------
    Html* Html::clone() const
    {
        return new Html(*this);
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string Html::getRaw() const
    {
        return "";
        //return data;
    }
//---------------------------------------------------------------------------------------------------------------------
//#####################################################################################################################
}
}
