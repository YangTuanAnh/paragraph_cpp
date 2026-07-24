#include "gui/pages.h"
#include "gui/utils.h"
#include "imgui.h"
#include "imguidatechooser.h"

void IUIPages::draw_page_tasks() {
    if (ImGui::Button("+ Add Task"))
        backend->add_task();

    static int filter_done = 0;
    static int filter_inbox = -1;
    static bool task_updated = 0;

    cycle_filter("Done", filter_done);
    ImGui::SameLine();
    cycle_filter("Inbox", filter_inbox);

    ImGui::Separator();

    auto &tasks = backend->get_tasks();

    if (ImGui::BeginTable("tasks", 7,
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                              ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_SizingStretchProp |
                              ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Task");
        ImGui::TableSetupColumn("Project");
        ImGui::TableSetupColumn("Done", ImGuiTableColumnFlags_WidthFixed, 60.f);
        ImGui::TableSetupColumn("Inbox", ImGuiTableColumnFlags_WidthFixed,
                                60.f);
        ImGui::TableSetupColumn("Urgency", ImGuiTableColumnFlags_WidthFixed,
                                80.f);
        ImGui::TableSetupColumn("Energy", ImGuiTableColumnFlags_WidthFixed,
                                80.f);
        ImGui::TableSetupColumn("Due At");

        ImGui::TableHeadersRow();

        for (int i = 0; i < tasks.size(); ++i) {
            auto &task = tasks[i];

            if (filter_done != -1 &&
                task.done != static_cast<bool>(filter_done))
                continue;

            if (filter_inbox != -1 &&
                task.inbox != static_cast<bool>(filter_inbox))
                continue;

            ImGui::PushID(task.id.empty() ? (void *)&task
                                          : (void *)task.id.c_str());

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            if (ImGui::Selectable(task.text.empty() ? "(Untitled)"
                                                    : task.text.c_str(),
                                  false))
                backend->open_task(task.id);

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Delete")) {
                    task.deleted = true;
                    task_updated = true;
                }

                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(1);

            const char *projectName = "None";

            if (auto project = backend->find_project(task.project_id))
                projectName = project->text.empty() ? "(Untitled)"
                                                    : project->text.c_str();

            if (ImGui::Selectable(projectName, false))
                backend->open_project(task.project_id);

            ImGui::TableSetColumnIndex(2);
            std::string doneLabel =
                std::string(task.done ? ICON_FA_CHECK : " ") + "##done" +
                std::to_string(i);
            if (ImGui::Selectable(doneLabel.c_str(), false)) {
                task.done = !task.done;
                task.updated = true;
                task_updated = true;
            }

            ImGui::TableSetColumnIndex(3);
            std::string inboxLabel =
                std::string(task.inbox ? ICON_FA_CHECK : " ") + "##inbox" +
                std::to_string(i);
            if (ImGui::Selectable(inboxLabel.c_str(), false)) {
                task.inbox = !task.inbox;
                task.updated = true;
                task_updated = true;
            }

            ImGui::TableSetColumnIndex(4);
            std::string urgencyLabel = std::string(urgency_icon(task.urgency)) +
                                       "##urgency" + std::to_string(i);
            if (ImGui::Selectable(urgencyLabel.c_str(), false))
                ImGui::OpenPopup("Urgency");

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("%s", urgency_name(task.urgency));

            if (ImGui::BeginPopup("Urgency")) {
                for (int i = 0; i <= static_cast<int>(Urgency::high); ++i) {
                    auto value = static_cast<Urgency>(i);
                    if (ImGui::Selectable(urgency_name(value),
                                          value == task.urgency)) {
                        task.urgency = value;
                        task.updated = true;
                        task_updated = true;
                    }
                }
                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(5);

            std::string energyLabel = std::string(energy_icon(task.energy)) +
                                      "##energy" + std::to_string(i);
            if (ImGui::Selectable(energyLabel.c_str(), false))
                ImGui::OpenPopup("Energy");

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("%s", energy_name(task.energy));

            if (ImGui::BeginPopup("Energy")) {
                for (int i = 0; i <= static_cast<int>(Energy::appointment);
                     ++i) {
                    auto value = static_cast<Energy>(i);
                    if (ImGui::Selectable(energy_name(value),
                                          value == task.energy)) {
                        task.energy = value;
                        task.updated = true;
                        task_updated = true;
                    }
                }
                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(6);

            std::tm tm{};
            if (task.due_at != 0)
                tm = *std::localtime(&task.due_at);
            else {
                std::time_t now = std::time(nullptr);
                tm = *std::localtime(&now);
            }

            if (ImGui::DateChooser(("##due" + std::to_string(i)).c_str(), tm)) {
                task.due_at = std::mktime(&tm);
                task.updated = true;
                task_updated = true;
            }
            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    if (task_updated) {
        backend->delete_tasks();
        backend->update_tasks();
        task_updated = !task_updated;
    }
}