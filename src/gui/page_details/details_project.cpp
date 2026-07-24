#include "imgui.h"
#include "imgui_stdlib.h"

#include "core/project.h"
#include "gui/pages.h"
#include "imguidatechooser.h"

void IUIPages::draw_details_project(bool &dirty) {
    const Selection &selection = backend->get_selection();

    Project *project = backend->find_project(selection.id);

    if (!project) {
        ImGui::TextDisabled("Project not found.");
        return;
    }

    ImGui::TextUnformatted("Project");
    ImGui::Separator();

    ImGui::InputText("Name", &project->text);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        project->updated = true;
        dirty = true;
    }

    const char *preview = "None";

    if (auto area = backend->find_area(project->area_id))
        preview = area->text.empty() ? "(Untitled)" : area->text.c_str();

    if (ImGui::BeginCombo("Area", preview)) {
        if (ImGui::Selectable("None", project->area_id.empty())) {
            project->area_id.clear();
            project->updated = true;
            dirty = true;
        }

        for (auto &area : backend->get_areas()) {
            bool selected = area.id == project->area_id;

            if (ImGui::Selectable(area.text.empty() ? "(Untitled)"
                                                    : area.text.c_str(),
                                  selected)) {
                project->area_id = area.id;
                project->updated = true;
                dirty = true;
            }

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (ImGui::Checkbox("Done", &project->done)) {
        project->updated = true;
        dirty = true;
    }

    ImGui::SameLine();

    if (ImGui::Checkbox("Archived", &project->archived)) {
        project->updated = true;
        dirty = true;
    }

    auto draw_time = [&](const char *label, std::time_t &t) {
        std::tm tm;

        if (t)
            tm = *std::localtime(&t);
        else {
            std::time_t now = std::time(nullptr);
            tm = *std::localtime(&now);
        }

        if (ImGui::DateChooser(label, tm)) {
            t = std::mktime(&tm);
            project->updated = true;
            dirty = true;
        }
    };

    draw_time("Start", project->start_at);
    draw_time("Due", project->due_at);

    ImGui::Separator();
    ImGui::TextUnformatted("Tasks");

    bool any = false;

    for (auto &task : backend->get_tasks()) {
        if (task.project_id != project->id)
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
    ImGui::TextWrapped("%s", project->id.c_str());
}