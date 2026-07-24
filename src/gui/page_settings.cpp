#include "gui/pages.h"
#include "imgui.h"


#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <cstdlib>
#else
#include <cstdlib>
#endif

void IUIPages::draw_page_settings() {
    constexpr const char *dataFolder = "data";

    ImGui::Text("Data Folder");
    ImGui::TextDisabled("%s",
                        std::filesystem::absolute(dataFolder).string().c_str());

    if (ImGui::Button("Open Data Folder")) {
        std::filesystem::create_directories(dataFolder);

#ifdef _WIN32
        ShellExecuteA(0, "open",
                      std::filesystem::absolute(dataFolder).string().c_str(), 0,
                      0, SW_SHOWNORMAL);
#elif __APPLE__
        std::string cmd =
            "open \"" + std::filesystem::absolute(dataFolder).string() + "\"";
        std::system(cmd.c_str());
#else
        std::string cmd = "xdg-open \"" +
                          std::filesystem::absolute(dataFolder).string() + "\"";
        std::system(cmd.c_str());
#endif
    }
}