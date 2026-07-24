#include "IconsFontAwesome6.h"
#include "gui/pages.h"
#include "gui/utils.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imguidatechooser.h"

#include <ctime>
void IUIPages::draw_page_areas() {
    if (ImGui::Button("+ Add Area"))
        backend->add_area();

    static int filter_done = -1;
    static int filter_archived = 0;
    static bool area_updated = false;

    cycle_filter("Done", filter_done);
    ImGui::SameLine();
    cycle_filter("Archived", filter_archived);

    ImGui::Separator();

    auto &curr_areas = backend->get_areas();

    if (ImGui::BeginTable("areas", 4,
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                              ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_SizingStretchProp |
                              ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Area");
        ImGui::TableSetupColumn("Done", ImGuiTableColumnFlags_WidthFixed, 60.f);
        ImGui::TableSetupColumn("Archived", ImGuiTableColumnFlags_WidthFixed,
                                80.f);
        ImGui::TableSetupColumn("Due At");
        ImGui::TableHeadersRow();

        for (int i = 0; i < curr_areas.size(); ++i) {
            auto &area = curr_areas[i];

            if (filter_done != -1 &&
                area.done != static_cast<bool>(filter_done))
                continue;

            if (filter_archived != -1 &&
                area.archived != static_cast<bool>(filter_archived))
                continue;

            ImGui::PushID(&area);

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            if (ImGui::Selectable(area.text.empty() ? "(Untitled)"
                                                    : area.text.c_str(),
                                  false))
                backend->open_area(area.id);

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Delete")) {
                    area.deleted = true;
                    area_updated = true;
                }
                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(1);
            std::string doneLabel =
                std::string(area.done ? ICON_FA_CHECK : " ") + "##done" +
                std::to_string(i);
            if (ImGui::Selectable(doneLabel.c_str(), false)) {
                area.done = !area.done;
                area.updated = true;
                area_updated = true;
            }

            ImGui::TableSetColumnIndex(2);
            std::string archivedLabel =
                std::string(area.archived ? ICON_FA_CHECK : " ") +
                "##archived" + std::to_string(i);
            if (ImGui::Selectable(archivedLabel.c_str(), false)) {
                area.archived = !area.archived;
                area.updated = true;
                area_updated = true;
            }

            ImGui::TableSetColumnIndex(3);
            std::tm tm;
            if (area.due_at != 0)
                tm = *std::localtime(&area.due_at);
            else {
                std::time_t now = std::time(nullptr);
                tm = *std::localtime(&now);
            }

            if (ImGui::DateChooser(("##due" + std::to_string(i)).c_str(), tm)) {
                area.due_at = std::mktime(&tm);
                area.updated = true;
                area_updated = true;
            }

            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    if (area_updated) {
        backend->delete_areas();
        backend->update_areas();
        area_updated = !area_updated;
    }
}