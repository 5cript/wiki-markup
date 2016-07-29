#include "component_factory.hpp"
#include "components/components.hpp"

#include <iostream>

namespace WikiMarkup
{
//#####################################################################################################################
    Components::IComponent* createComponent(std::string const& type, JSON::ObjectReader const& jsonData)
    {
        using namespace Components;

        #define GET_TYPE_NAME(COMPONENT) \
            COMPONENT::getMetaInfoS().name

        #define CREATE_BY_NAME(Component) \
            if(type == GET_TYPE_NAME(Component)) \
            { \
                component.reset(new Component); \
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
        else return nullptr;

        component->fromJson(jsonData);
        return component.release();
    }
//#####################################################################################################################
}
