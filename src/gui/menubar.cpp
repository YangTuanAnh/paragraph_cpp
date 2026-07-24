#include "gui/menubar.h"
#include "imgui.h"

void Menubar::draw_menubar(bool &running, bool &showDemoWindow,
                           bool &show_inspector) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit"))
                running = false;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            // if (ImGui::MenuItem("Demo Window", nullptr, showDemoWindow))
            //     showDemoWindow = !showDemoWindow;

            if (ImGui::MenuItem("Inspector", nullptr, show_inspector))
                show_inspector = !show_inspector;

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
