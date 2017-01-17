#pragma once

#include "exportable_components/exportable_list.hpp"

#include "component.hpp"

namespace WikiMarkup { namespace Components {

    // this format is well parsable, but not useful for actual use
    using PlainList = std::vector <ListLine>;

    struct List : public IComponent
                , public ExportableList
    {
        std::string toMarkup() override;
        ParsingResult fromMarkup(std::string const& mu) override;

        WMC_EXPORTABLE_DELEGATION_HEADER;

        MetaInfo getMetaInfo() const override;
        static MetaInfo getMetaInfoS();
        List* clone() const override;
    };

} // namespace Components
} // namespace WikiMarkup

BOOST_FUSION_ADAPT_STRUCT
(
    WikiMarkup::Components::List,
    (WikiMarkup::Components::PrimalList, list)
)
