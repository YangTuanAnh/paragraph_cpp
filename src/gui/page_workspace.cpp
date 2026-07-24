#include "core/task.h"
#include "gui/pages.h"
#include "gui/utils.h"
#include "imgui.h"


void IUIPages::draw_page_workspace() {
    static bool task_updated = 0;
    auto &tasks = backend->get_tasks();
    auto &projects = backend->get_projects();
    auto &areas = backend->get_areas();
    auto &resources = backend->get_resources();
    if (!ImGui::BeginTable("workspace", 2,
                           ImGuiTableFlags_Resizable |
                               ImGuiTableFlags_BordersInnerV |
                               ImGuiTableFlags_SizingStretchSame))
        return;

    auto draw_task = [&](Task &task) {
        ImGui::PushID(task.id.c_str());

        if (ImGui::Checkbox("##done", &task.done)) {
            task.updated = true;
            task_updated = true;
        }

        ImGui::SameLine();

        ImGui::TextUnformatted(urgency_icon(task.urgency));
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s", urgency_name(task.urgency));

        ImGui::SameLine();

        ImGui::TextUnformatted(energy_icon(task.energy));
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s", energy_name(task.energy));

        ImGui::SameLine();

        if (ImGui::Selectable(task.text.empty() ? "(Untitled)"
                                                : task.text.c_str())) {
            backend->open_task(task.id);
        }

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete")) {
                task.deleted = true;
                backend->delete_tasks();
            }

            ImGui::EndPopup();
        }

        ImGui::PopID();
    };

    ImGui::TableNextColumn();

    ImGui::TextUnformatted("Inbox");
    ImGui::Separator();

    ImGui::PushID("Inbox");
    for (auto &task : tasks) {
        if (!task.inbox || task.archived)
            continue;

        draw_task(task);
    }
    ImGui::PopID();

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::TextUnformatted("Next Actions");
    ImGui::Separator();

    ImGui::PushID("Next Actions");
    for (auto &task : tasks) {
        if (task.inbox || task.archived || task.done)
            continue;

        draw_task(task);
    }
    ImGui::PopID();

    ImGui::TableNextColumn();

    ImGui::TextUnformatted("Projects");
    ImGui::Separator();

    for (auto &project : projects) {
        if (project.archived)
            continue;

        int total = 0;
        int done = 0;

        for (auto &task : tasks) {
            if (task.project_id != project.id)
                continue;

            total++;

            if (task.done)
                done++;
        }

        float progress = total == 0 ? 0.f : float(done) / float(total);

        ImGui::PushID(project.id.c_str());

        if (ImGui::Selectable(project.text.empty() ? "(Untitled)"
                                                   : project.text.c_str())) {
            backend->open_project(project.id);
        }

        ImGui::ProgressBar(
            progress, ImVec2(-1, 0),
            (std::to_string(done) + "/" + std::to_string(total)).c_str());

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::TextUnformatted("Areas");
    ImGui::Separator();

    for (auto &area : areas) {
        if (area.archived)
            continue;

        int projectsCount = 0;
        int tasksCount = 0;

        for (auto &project : projects) {
            if (project.area_id != area.id || project.archived)
                continue;

            projectsCount++;

            for (auto &task : tasks)
                if (task.project_id == project.id && !task.archived)
                    tasksCount++;
        }

        ImGui::PushID(area.id.c_str());

        if (ImGui::Selectable(area.text.empty() ? "(Untitled)"
                                                : area.text.c_str())) {
            backend->open_area(area.id);
        }

        ImGui::SameLine();
        ImGui::TextDisabled("%d projects • %d tasks", projectsCount,
                            tasksCount);

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::TextUnformatted("Resources");
    ImGui::Separator();

    for (auto &resource : resources) {
        if (resource.archived)
            continue;

        auto *area = backend->find_area(resource.area_id);

        if (!area || area->archived)
            continue;

        ImGui::PushID(resource.id.c_str());

        if (ImGui::Selectable(resource.text.empty() ? "(Untitled)"
                                                    : resource.text.c_str())) {
            backend->open_resource(resource.id);
        }

        if (ImGui::BeginPopupContextItem("ResourcePopup")) {
            if (ImGui::MenuItem("Open"))
                backend->open_resource(resource.id);

            if (ImGui::MenuItem("Open Area"))
                backend->open_area(area->id);

            ImGui::EndPopup();
        }

        ImGui::SameLine();
        ImGui::TextDisabled("%s", area->text.empty() ? "(Untitled Area)"
                                                     : area->text.c_str());

        ImGui::PopID();
    }

    ImGui::EndTable();

    if (task_updated) {
        backend->delete_tasks();
        backend->update_tasks();
        task_updated = !task_updated;
    }
}