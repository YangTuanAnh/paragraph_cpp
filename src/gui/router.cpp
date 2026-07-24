#include "gui/router.h"
#include "core/backend.h"
#include "gui/pages.h"
#include "imgui.h"

void Router::draw_taskbar(Page &current_page, Backend &backend) {
    float toolbarWidth =
        std::max(100.0f, ImGui::GetContentRegionAvail().x * 0.125f);
    ImGui::BeginChild("Toolbar", ImVec2(toolbarWidth, 0.0f));
    if (ImGui::Selectable("Workspace", current_page == Page::Workspace))
        current_page = Page::Workspace;

    if (ImGui::Selectable("Graph View", current_page == Page::Graph_View)) {
        backend.invalidate_graph();
        backend.layout_graph();
        current_page = Page::Graph_View;
    }

    if (ImGui::Selectable("Tasks", current_page == Page::Tasks))
        current_page = Page::Tasks;

    if (ImGui::Selectable("Projects", current_page == Page::Projects))
        current_page = Page::Projects;

    if (ImGui::Selectable("Areas", current_page == Page::Areas))
        current_page = Page::Areas;

    if (ImGui::Selectable("Resources", current_page == Page::Resources))
        current_page = Page::Resources;

    // if (ImGui::Selectable("Archived", current_page == Page::Archived))
    //     current_page = Page::Archived;

    if (ImGui::Selectable("Settings", current_page == Page::Settings))
        current_page = Page::Settings;

    ImGui::EndChild();
}

void Router::draw_page(Page &current_page) {
    switch (current_page) {
    case Page::Workspace:
        IUIPages::draw_page_workspace();
        break;
    case Page::Graph_View:
        IUIPages::draw_page_graph();
        break;
    case Page::Tasks:
        IUIPages::draw_page_tasks();
        break;
    case Page::Projects:
        IUIPages::draw_page_projects();
        break;
    case Page::Areas:
        IUIPages::draw_page_areas();
        break;
    case Page::Resources:
        IUIPages::draw_page_resources();
        break;
    case Page::Archived:
        break;
    case Page::Settings:
        IUIPages::draw_page_settings();
        break;
    default:
        break;
    }
}