#include "core/task.h"
#include "gui/pages.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imguidatechooser.h"


void IUIPages::draw_details_task(bool &dirty) {
    const Selection &selection = backend->get_selection();
    auto *task = backend->find_task(selection.id);

    if (!task)
        return;

    ImGui::TextUnformatted("Task");
    ImGui::Separator();

    ImGui::InputText("Name", &task->text);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        task->updated = true;
        dirty = true;
    }

    const char *preview = "None";

    if (auto project = backend->find_project(task->project_id))
        preview = project->text.empty() ? "(Untitled)" : project->text.c_str();

    if (ImGui::BeginCombo("Project", preview)) {
        if (ImGui::Selectable("None", task->project_id.empty())) {
            task->project_id.clear();
            task->updated = true;
            dirty = true;
        }

        for (auto &project : backend->get_projects()) {
            bool selected = project.id == task->project_id;

            if (ImGui::Selectable(project.text.empty() ? "(Untitled)"
                                                       : project.text.c_str(),
                                  selected)) {
                task->project_id = project.id;
                task->updated = true;
                dirty = true;
            }

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (ImGui::Checkbox("Done", &task->done)) {
        task->updated = true;
        dirty = true;
    }

    ImGui::SameLine();

    if (ImGui::Checkbox("Inbox", &task->inbox)) {
        task->updated = true;
        dirty = true;
    }

    ImGui::SameLine();

    if (ImGui::Checkbox("Archived", &task->archived)) {
        task->updated = true;
        dirty = true;
    }

    static const char *urgency_names[] = {"None", "Low", "Medium", "High"};

    int urgency = static_cast<int>(task->urgency);

    if (ImGui::Combo("Urgency", &urgency, urgency_names,
                     IM_ARRAYSIZE(urgency_names))) {
        task->urgency = static_cast<Urgency>(urgency);
        task->updated = true;
        dirty = true;
    }

    static const char *energy_names[] = {
        "None", "Trivial",     "Easy",      "Medium",
        "Hard", "Challenging", "Breakdown", "Appointment"};

    int energy = static_cast<int>(task->energy);

    if (ImGui::Combo("Energy", &energy, energy_names,
                     IM_ARRAYSIZE(energy_names))) {
        task->energy = static_cast<Energy>(energy);
        task->updated = true;
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
            task->updated = true;
            dirty = true;
        }
    };

    draw_time("Start", task->start_at);
    draw_time("Due", task->due_at);

    ImGui::Separator();
    ImGui::TextUnformatted("Hierarchy");

    if (auto project = backend->find_project(task->project_id)) {
        if (ImGui::Selectable(project->text.empty() ? "(Untitled)"
                                                    : project->text.c_str()))
            backend->open_project(project->id);

        if (auto area = backend->find_area(project->area_id)) {
            ImGui::Indent();

            if (ImGui::Selectable(area->text.empty() ? "(Untitled)"
                                                     : area->text.c_str()))
                backend->open_area(area->id);

            ImGui::Unindent();
        }
    } else {
        ImGui::TextDisabled("No project");
    }

    ImGui::Separator();
    ImGui::TextDisabled("ID");
    ImGui::TextWrapped("%s", task->id.c_str());
}