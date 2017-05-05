#include "exp_component_factory.hpp"
#include "components/exportable_components/exportable_components.hpp"

namespace WikiMarkup
{
//#####################################################################################################################
    DLL_EXPORT Components::IExportableComponent* createExportableComponent(std::string const& type, JSON::ObjectReader const& jsonData)
    {
        using namespace Components;

        #define GET_TYPE_NAME(COMPONENT) \
            COMPONENT::getMetaInfoS().name

        #define CREATE_BY_NAME(Component) \
            if(type == GET_TYPE_NAME(Component)) \
            { \
                component.reset(new Component); \
            }

        std::unique_ptr <IExportableComponent> component {nullptr};

        CREATE_BY_NAME(ExportableCommentText)
        else CREATE_BY_NAME(ExportableHeader)
        else CREATE_BY_NAME(ExportableHorizontalLine)
        else CREATE_BY_NAME(ExportableLink)
        else CREATE_BY_NAME(ExportableList)
        else CREATE_BY_NAME(ExportablePreformattedText)
        else CREATE_BY_NAME(ExportableTable)
        else CREATE_BY_NAME(ExportableText)
        else CREATE_BY_NAME(ExportableHtml)
        else CREATE_BY_NAME(ExportableRichText)
        else CREATE_BY_NAME(ExportableImageRegion)
        else return nullptr;

        component->fromJson(jsonData);
        return component.release();
    }
//#####################################################################################################################
}
