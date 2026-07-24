#include "IconsFontAwesome6.h"
#include "gui/pages.h"
#include "gui/utils.h"
#include "imgui.h"
#include "imguidatechooser.h"

void IUIPages::draw_page_projects() {
    if (ImGui::Button("+ Add Project"))
        backend->add_project();

    static int filter_done = -1;
    static int filter_archived = 0;
    static bool project_updated = 0;

    cycle_filter("Done", filter_done);
    ImGui::SameLine();
    cycle_filter("Archived", filter_archived);

    ImGui::Separator();

    auto &projects = backend->get_projects();

    if (ImGui::BeginTable("projects", 5,
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                              ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_SizingStretchProp |
                              ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Area");
        ImGui::TableSetupColumn("Done", ImGuiTableColumnFlags_WidthFixed, 60.f);
        ImGui::TableSetupColumn("Archived", ImGuiTableColumnFlags_WidthFixed,
                                80.f);
        ImGui::TableSetupColumn("Due At");
        ImGui::TableHeadersRow();

        for (int i = 0; i < projects.size(); ++i) {
            auto &project = projects[i];

            if (filter_done != -1 &&
                project.done != static_cast<bool>(filter_done))
                continue;

            if (filter_archived != -1 &&
                project.archived != static_cast<bool>(filter_archived))
                continue;

            ImGui::PushID(project.id.c_str());

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            if (ImGui::Selectable(project.text.empty() ? "(Untitled)"
                                                       : project.text.c_str(),
                                  false))
                backend->open_project(project.id);

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Delete")) {
                    project.deleted = true;
                    project_updated = true;
                }

                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(1);

            const char *areaName = "None";

            if (auto area = backend->find_area(project.area_id))
                areaName =
                    area->text.empty() ? "(Untitled)" : area->text.c_str();

            if (ImGui::Selectable(areaName, false))
                backend->open_area(project.area_id);

            ImGui::TableSetColumnIndex(2);
            std::string doneLabel =
                std::string(project.done ? ICON_FA_CHECK : " ") + "##done" +
                std::to_string(i);
            if (ImGui::Selectable(doneLabel.c_str(), false)) {
                project.done = !project.done;
                project.updated = true;
                project_updated = true;
            }

            ImGui::TableSetColumnIndex(3);
            std::string archivedLabel =
                std::string(project.archived ? ICON_FA_CHECK : " ") +
                "##archived" + std::to_string(i);
            if (ImGui::Selectable(archivedLabel.c_str(), false)) {
                project.archived = !project.archived;
                project.updated = true;
                project_updated = true;
            }

            ImGui::TableSetColumnIndex(4);
            std::tm tm;

            if (project.due_at != 0)
                tm = *std::localtime(&project.due_at);
            else {
                std::time_t now = std::time(nullptr);
                tm = *std::localtime(&now);
            }

            if (ImGui::DateChooser(("##due" + std::to_string(i)).c_str(), tm)) {
                project.due_at = std::mktime(&tm);
                project.updated = true;
            }

            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    if (project_updated) {
        backend->delete_projects();
        backend->update_projects();
        project_updated = !project_updated;
    }
}