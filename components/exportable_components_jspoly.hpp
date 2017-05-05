#pragma once

#include "exportable_components/exportable_components.hpp"

JSON_DECLARE_POLYMORPHIC
(
    WikiMarkup::Components::IExportableComponent,
    (WikiMarkup::Components::ExportableCommentText)
    (WikiMarkup::Components::ExportableHeader)
    (WikiMarkup::Components::ExportableHorizontalLine)
    (WikiMarkup::Components::ExportableHtml)
    (WikiMarkup::Components::ExportableImageRegion)
    (WikiMarkup::Components::ExportableLink)
    (WikiMarkup::Components::ExportableList)
    (WikiMarkup::Components::ExportablePreformattedText)
    (WikiMarkup::Components::ExportableRichText)
    (WikiMarkup::Components::ExportableTable)
    (WikiMarkup::Components::ExportableText)
)
