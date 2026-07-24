#include "core/area.h"
#include "gui/pages.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imguidatechooser.h"


void IUIPages::draw_details_area(bool &dirty) {
    const Selection &selection = backend->get_selection();

    Area *area = backend->find_area(selection.id);

    if (!area) {
        ImGui::TextDisabled("Area not found.");
        return;
    }

    ImGui::TextUnformatted("Area");
    ImGui::Separator();

    ImGui::InputText("Name", &area->text);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        area->updated = true;
        dirty = true;
    }

    ImGui::InputText("Category", &area->category);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        area->updated = true;
        dirty = true;
    }

    if (ImGui::Checkbox("Done", &area->done)) {
        area->updated = true;
        dirty = true;
    }

    if (ImGui::Checkbox("Archived", &area->archived)) {
        area->updated = true;
        dirty = true;
    }

    auto draw_time = [&](const char *label, std::time_t &value) {
        std::tm tm;

        if (value != 0)
            tm = *std::localtime(&value);
        else {
            std::time_t now = std::time(nullptr);
            tm = *std::localtime(&now);
        }

        if (ImGui::DateChooser(label, tm)) {
            value = std::mktime(&tm);
            area->updated = true;
            dirty = true;
        }
    };

    draw_time("Start", area->start_at);
    draw_time("Due", area->due_at);

    ImGui::Separator();
    ImGui::TextUnformatted("Resources");

    bool any = false;

    for (auto &resource : backend->get_resources()) {
        if (resource.area_id != area->id)
            continue;

        any = true;

        if (ImGui::Selectable(resource.text.empty() ? "(Untitled)"
                                                    : resource.text.c_str()))
            backend->open_resource(resource.id);
    }

    if (!any)
        ImGui::TextDisabled("None");

    ImGui::Separator();
    ImGui::TextUnformatted("Projects");

    any = false;

    for (auto &project : backend->get_projects()) {
        if (project.area_id != area->id)
            continue;

        any = true;

        if (ImGui::Selectable(project.text.empty() ? "(Untitled)"
                                                   : project.text.c_str()))
            backend->open_project(project.id);
    }

    if (!any)
        ImGui::TextDisabled("None");

    ImGui::Separator();
    ImGui::TextUnformatted("Tasks");

    any = false;

    for (auto &task : backend->get_tasks()) {
        auto *project = backend->find_project(task.project_id);

        if (!project || project->area_id != area->id)
            continue;

        any = true;

        if (ImGui::Selectable(task.text.empty() ? "(Untitled)"
                                                : task.text.c_str()))
            backend->open_task(task.id);
    }

    if (!any)
        ImGui::TextDisabled("None");

    ImGui::Separator();
    ImGui::TextDisabled("ID");
    ImGui::TextWrapped("%s", area->id.c_str());
}