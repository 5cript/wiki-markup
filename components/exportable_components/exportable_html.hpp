#pragma once

#include "SimpleUtil/value_ptr/value_ptr.hpp"
#include "exportable_component.hpp"

namespace WikiMarkup { namespace Components
{
    struct RawHtmlTreeNode : public JSON::Stringifiable <RawHtmlTreeNode>
                           , public JSON::Parsable <RawHtmlTreeNode>
    {
        using parameters_type = std::map <std::string, std::string>;
        using content_or_node = std::pair <std::string, boost::optional <RawHtmlTreeNode>>;

        std::string name;
        parameters_type parameters;
        std::vector <content_or_node> children;
        bool has_content;
    };

    struct HtmlTreeNode : public JSON::Stringifiable <HtmlTreeNode>
                        , public JSON::Parsable <HtmlTreeNode>
    {
        using parameters_type = RawHtmlTreeNode::parameters_type;

        std::string name;
        parameters_type parameters;
        std::vector <sutil::value_ptr <IExportableComponent>> children;
        bool has_content;
    };

    struct ExportableHtml : public virtual IExportableComponent
                          , public JSON::Stringifiable <ExportableHtml>
                          , public JSON::Parsable <ExportableHtml>
    {
        HtmlTreeNode tree;
        // std::string data;

        ExportableHtml() = default;
        ExportableHtml(HtmlTreeNode const& tree);
        std::string toJson() const override;
        void fromJson(std::string const& str) override;
        void fromJson(JSON::ObjectReader const& reader) override;
        ExportableHtml* clone() const override;

        static MetaInfo getMetaInfoS() { return {"Html", false}; }
    };
}
}

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::RawHtmlTreeNode,
    (std::string, name) // 0
    (WikiMarkup::Components::RawHtmlTreeNode::parameters_type, parameters) // 1
    (std::vector <WikiMarkup::Components::RawHtmlTreeNode::content_or_node>, children) // 2
    (bool, has_content) // 3
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::HtmlTreeNode,
    (std::string, name) // 0
    (WikiMarkup::Components::HtmlTreeNode::parameters_type, parameters) // 1
    (std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>>, children) // 2
    (bool, has_content) // 3
)

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::ExportableHtml,
    //(std::string, data)
    (WikiMarkup::Components::HtmlTreeNode, tree)
)
