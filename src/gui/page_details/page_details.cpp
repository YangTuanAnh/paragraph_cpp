#include "gui/pages.h"
#include "imgui.h"

void IUIPages::draw_panel_details() {
    const Selection &selection = backend->get_selection();
    static bool area_updated = 0;
    static bool project_updated = 0;
    static bool task_updated = 0;
    static bool resource_updated = 0;

    if (selection.type == SelectionType::None) {
        ImGui::TextDisabled("Nothing selected.");
        ImGui::Separator();
        ImGui::TextWrapped(
            "Select an Area, Project, Task or Resource from any page "
            "to edit its properties and browse related items.");
        return;
    }

    switch (selection.type) {
    case SelectionType::Area:
        IUIPages::draw_details_area(area_updated);
        break;

    case SelectionType::Project:
        IUIPages::draw_details_project(project_updated);
        break;

    case SelectionType::Task:
        IUIPages::draw_details_task(task_updated);
        break;

    case SelectionType::Resource:
        IUIPages::draw_details_resource(resource_updated);
        break;

    default:
        ImGui::TextDisabled("Unsupported selection.");
        break;
    }

    if (area_updated) {
        backend->delete_areas();
        backend->update_areas();
        area_updated = !area_updated;
    }

    if (project_updated) {
        backend->delete_projects();
        backend->update_projects();
        project_updated = !project_updated;
    }

    if (task_updated) {
        backend->delete_tasks();
        backend->update_tasks();
        task_updated = !task_updated;
    }

    if (resource_updated) {
        backend->delete_resources();
        backend->update_resources();
        resource_updated = !resource_updated;
    }
}