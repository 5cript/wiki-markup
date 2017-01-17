#pragma once

#include "components/exportable_components/exportable_components.hpp"
#include "SimpleUtil/value_ptr/value_ptr.hpp"

#include <vector>
#include <memory>
#include <iosfwd>
#include <type_traits>

namespace WikiMarkup
{
    class ExportablePage
    {
    private:
        std::vector <sutil::value_ptr <Components::IExportableComponent>> components_;

    public:
        ExportablePage() = default;
        virtual ~ExportablePage() = default;

        /**
         *  Adds a component to the page.
         */
        template <typename T>
        void appendComponent(T const&& comp)
        {
            components_.emplace_back (new T(std::move(comp)));
        }

        /**
         *  Adds a component to the page.
         */
        void appendComponent(Components::IExportableComponent const& component);

        /**
         *  Adds a component to the page.
         */
        void appendComponent(Components::IExportableComponent* component);

        /**
         *  Get all components of the page.
         */
		std::add_lvalue_reference <decltype(components_)>::type getComponents();

		/**
		 *  Set all components of the page.
		 */
		void setComponents(decltype(components_) const& components);

        /**
         *  Wipe the page clear.
         */
        void clear();

        /**
         *  Generates a json string from the internal representation.
         */
        std::string toJson() const;

        /**
         *  Generates the components from JSON.
         */
        void fromJson(std::string const& json);
    };
}
