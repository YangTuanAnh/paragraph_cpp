#include "core/resource.h"
#include "gui/pages.h"
#include "imgui.h"
#include "imgui_stdlib.h"

void IUIPages::draw_details_resource(bool &dirty) {
    const Selection &selection = backend->get_selection();

    Resource *resource = backend->find_resource(selection.id);

    if (!resource) {
        ImGui::TextDisabled("Resource not found.");
        return;
    }

    ImGui::TextUnformatted("Resource");
    ImGui::Separator();

    ImGui::InputText("Name", &resource->text);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        resource->updated = true;
        dirty = true;
    }

    ImGui::InputText("Source", &resource->source);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        resource->updated = true;
        dirty = true;
    }

    static const char *types[] = {"None", "File",     "Folder",
                                  "URL",  "Article",  "Video",
                                  "Book", "Document", "Other"};

    int type = static_cast<int>(resource->resource_type);

    if (ImGui::Combo("Type", &type, types, IM_ARRAYSIZE(types))) {
        resource->resource_type = static_cast<ResourceType>(type);
        resource->updated = true;
        dirty = true;
    }

    const char *preview = "None";

    if (auto area = backend->find_area(resource->area_id))
        preview = area->text.empty() ? "(Untitled)" : area->text.c_str();

    if (ImGui::BeginCombo("Area", preview)) {
        if (ImGui::Selectable("None", resource->area_id.empty())) {
            resource->area_id.clear();
            resource->updated = true;
            dirty = true;
        }

        for (auto &area : backend->get_areas()) {
            bool selected = area.id == resource->area_id;

            if (ImGui::Selectable(area.text.empty() ? "(Untitled)"
                                                    : area.text.c_str(),
                                  selected)) {
                resource->area_id = area.id;
                resource->updated = true;
                dirty = true;
            }

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (ImGui::Checkbox("Archived", &resource->archived)) {
        resource->updated = true;
        dirty = true;
    }

    ImGui::Separator();
    ImGui::TextDisabled("ID");
    ImGui::TextWrapped("%s", resource->id.c_str());
}