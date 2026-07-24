#include "IconsFontAwesome6.h"
#include "imgui.h"

#include "core/resource.h"
#include "gui/pages.h"
#include "gui/utils.h"

static const char *resource_type_names[] = {"None", "File",     "Folder",
                                            "URL",  "Article",  "Video",
                                            "Book", "Document", "Other"};

void IUIPages::draw_page_resources() {
    if (ImGui::Button("+ Add Resource"))
        backend->add_resource();

    static int filter_archived = 0;
    static bool resource_updated = 0;

    cycle_filter("Archived", filter_archived);

    ImGui::Separator();

    auto &resources = backend->get_resources();

    if (ImGui::BeginTable("resources", 5,
                          ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                              ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_SizingStretchProp |
                              ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Area");
        ImGui::TableSetupColumn("Source");
        ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 90.f);
        ImGui::TableSetupColumn("Archived", ImGuiTableColumnFlags_WidthFixed,
                                80.f);

        ImGui::TableHeadersRow();

        for (int i = 0; i < resources.size(); ++i) {
            auto &resource = resources[i];

            if (filter_archived != -1 &&
                resource.archived != static_cast<bool>(filter_archived))
                continue;

            ImGui::PushID(resource.id.c_str());

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            if (ImGui::Selectable(resource.text.empty() ? "(Untitled)"
                                                        : resource.text.c_str(),
                                  false))
                backend->open_resource(resource.id);

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Delete")) {
                    resource.deleted = true;
                    resource_updated = true;
                }

                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(1);

            const char *areaName = "None";

            if (auto area = backend->find_area(resource.area_id))
                areaName =
                    area->text.empty() ? "(Untitled)" : area->text.c_str();

            if (ImGui::Selectable(areaName, false))
                backend->open_area(resource.area_id);

            ImGui::TableSetColumnIndex(2);
            switch (resource.resource_type) {
            case ResourceType::url:
                ImGui::TextLinkOpenURL(resource.source.c_str(),
                                       resource.source.c_str());
                break;

                // case ResourceType::file:
                // case ResourceType::folder:
                // case ResourceType::document:
                //     // open_file(resource.source);
                //     break;

            default:
                ImGui::TextUnformatted(resource.source.c_str());
                break;
            }

            if (ImGui::IsItemHovered() && !resource.source.empty()) {
                ImGui::SetTooltip("%s", resource.source.c_str());
            }

            ImGui::TableSetColumnIndex(3);
            std::string resourceLabel =
                std::string(resource_type_names[(int)resource.resource_type]) +
                "##" + std::to_string(i);
            if (ImGui::Selectable(resourceLabel.c_str(), false))
                ImGui::OpenPopup("Type");

            if (ImGui::BeginPopup("Type")) {
                for (int j = 0; j <= (int)ResourceType::other; ++j) {
                    auto value = (ResourceType)j;

                    if (ImGui::Selectable(resource_type_names[j],
                                          value == resource.resource_type)) {
                        resource.resource_type = value;
                        resource.updated = true;
                        resource_updated = true;
                    }
                }

                ImGui::EndPopup();
            }

            ImGui::TableSetColumnIndex(4);
            std::string archivedLabel =
                std::string(resource.archived ? ICON_FA_CHECK : " ") +
                "##archived" + std::to_string(i);

            if (ImGui::Selectable(archivedLabel.c_str(), false)) {
                resource.archived = !resource.archived;
                resource.updated = true;
                resource_updated = true;
            }

            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    if (resource_updated) {
        backend->delete_resources();
        backend->update_resources();
        resource_updated = !resource_updated;
    }
}