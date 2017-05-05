#pragma once

#include "../../SimpleUtil/value_ptr/cloneable.hpp"
#include "twisted-spirit/core/parsing_results.hpp"
#include "exportable_components/exportable_component.hpp"

#include "meta_info.hpp"

#include <string>

namespace WikiMarkup { namespace Components {

    using namespace sutil;
    using namespace TwistedSpirit;

    class IComponent : public virtual IExportableComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual std::string toMarkup() = 0;
        virtual ParsingResult fromMarkup(std::string const&) = 0;
        virtual MetaInfo getMetaInfo() const = 0;

        virtual IComponent* clone() const = 0;
    };

    #define WMC_EXPORTABLE_DELEGATION_HEADER \
        std::string toJson() const override; \
        void fromJson(std::string const&) override; \
        void fromJson(JSON::ObjectReader const& reader) override

    #define WMC_EXPORTABLE_DELEGATION_SOURCE(TYPE) \
        std::string TYPE::toJson() const \
        { \
            return Exportable##TYPE::toJson(); \
        } \
        void TYPE::fromJson(std::string const& str) \
        { \
            Exportable##TYPE::fromJson(str); \
        } \
        void TYPE::fromJson(JSON::ObjectReader const& reader) \
        { \
            Exportable##TYPE::fromJson(reader); \
        }


} // namespace Components
} // namespace WikiMarkup
