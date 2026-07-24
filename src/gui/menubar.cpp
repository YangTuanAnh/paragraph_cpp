#include "gui/menubar.h"
#include "gui/theme.h"
#include "imgui.h"

void Menubar::draw_menubar(bool &running, bool &showDemoWindow,
                           bool &show_inspector, int &theme_index) {
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
        if (ImGui::BeginMenu("Theme")) {
            for (size_t i = 0; i < theme_functions.size(); ++i) {
                if (ImGui::RadioButton(theme_names[i], theme_index == static_cast<int>(i))) {
                    theme_index = static_cast<int>(i);
                    theme_functions[theme_index]();
                }
            }
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
}
