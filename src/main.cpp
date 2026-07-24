#include "imgui.h"
#include "imnodes.h"
#include "raylib.h"
#include "rlImGui.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>

#include "core/backend.h"
#include "gui/menubar.h"
#include "gui/pages.h"
#include "gui/router.h"

Backend *IUIPages::backend = nullptr;

int main(int argc, char *argv[]) {
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Paragraph");
    Image logo = LoadImage("data/tabby.png");
    ImageFormat(&logo, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(logo);
    UnloadImage(logo);

    SetTargetFPS(60);
    rlImGuiSetup(true);
    ImNodes::CreateContext();

    // Backend initialization
    Backend backend;
    IUIPages::backend = &backend;

    Page current_page = Page::Workspace;

    // Main game loop
    bool running = true;
    bool showDemoWindow = true;
    bool show_inspector = true;
    while (running && !WindowShouldClose()) {
        BeginDrawing();

        // start ImGui Content
        rlImGuiBegin();

        // Our menu bar
        Menubar::draw_menubar(running, showDemoWindow, show_inspector);

        // This is the main display area, that fills the app's window
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        if (ImGui::Begin("Main Window", nullptr,
                         ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoBringToFrontOnFocus)) {
            // The toolbar
            Router::draw_taskbar(current_page, backend);

            ImGui::SameLine();

            // The main display
            ImGui::BeginChild("Main", ImVec2(0.0f, 0.0f), ImGuiChildFlags_None,
                              ImGuiWindowFlags_HorizontalScrollbar);

            Router::draw_page(current_page);

            ImGui::EndChild();
        }
        ImGui::End();

        if (show_inspector) {
            ImGui::Begin("Inspector");
            IUIPages::draw_panel_details();
            ImGui::End();
        }

        // if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

        // End ImGui Content
        rlImGuiEnd();

        // ##### INSERT ANY ADDITIONAL RENDERING YOU WANT TO DO OVER THE GUI
        // HERE #####

        EndDrawing();
    }
    ImNodes::DestroyContext();
    rlImGuiShutdown();

    // Cleanup
    rlImGuiShutdown();
    CloseWindow();

    return EXIT_SUCCESS;
}