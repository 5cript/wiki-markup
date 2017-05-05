#pragma once

#include "exportable_components/exportable_html.hpp"

#include "component.hpp"
#include "twisted-spirit/core/parsing_results.hpp"

namespace WikiMarkup { namespace Components
{
    using namespace TwistedSpirit;

    struct Html : public IComponent
                , public ExportableHtml
    {
        Html() = default;
        Html(HtmlTreeNode const& tree);
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        Html* clone() const override;
        std::string getRaw() const;
    };

} // Components
} // WikiMarkup

BOOST_FUSION_ADAPT_STRUCT(WikiMarkup::Components::Html, tree)
