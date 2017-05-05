#include "promote_component.hpp"

#include "components/exportable_components/exportable_components.hpp"
#include "components/components.hpp"
#include "components/exportable_components_jspoly.hpp"

#include "conversion.hpp"

#include <iostream>

namespace WikiMarkup
{
//#####################################################################################################################
    Components::IComponent* promoteComponent(Components::IExportableComponent* exportable)
    {
        using namespace Components;

        auto json = exportable->toJson();

        #define CREATE_BY_NAME(Component) \
            if(dynamic_cast <Exportable ## Component*> (exportable)) \
            { \
                component.reset(new Component); \
                fromJson <Component> (*static_cast <Component*> (component.get()), json, true); \
            }

        std::unique_ptr <IComponent> component {nullptr};

        CREATE_BY_NAME(CommentText)
        else CREATE_BY_NAME(Header)
        else CREATE_BY_NAME(HorizontalLine)
        else CREATE_BY_NAME(Link)
        else CREATE_BY_NAME(List)
        else CREATE_BY_NAME(PreformattedText)
        else CREATE_BY_NAME(Table)
        else CREATE_BY_NAME(Text)
        else CREATE_BY_NAME(Html)
        else CREATE_BY_NAME(RichText)
        //else CREATE_BY_NAME(ImageRegion)
        else return nullptr;

        return component.release();
    }
//---------------------------------------------------------------------------------------------------------------------
//#####################################################################################################################
}
