#ifndef THEME_H_
#define THEME_H_

#include <cstdint>
#include <functional>
#include <vector>
// guard
#include <imgui.h>

void theme_dark() { ImGui::StyleColorsDark(); }

void theme_light() { ImGui::StyleColorsLight(); }

void theme_classic() { ImGui::StyleColorsClassic(); }

/**
 * Credit to https://github.com/GraphicsProgramming/dear-imgui-styles
 */
void theme_spectrum() {
    using namespace ImGui;
    ImGuiStyle* style = &ImGui::GetStyle();
    style->GrabRounding = 4.0f;

    // ImGui ImU32 format is 0xAABBGGRR; standard RGB literals are 0xRRGGBB.
    // Swap R and B channels and add full alpha.
    auto Color = [](uint32_t c, uint32_t a = 0xFF) -> uint32_t {
        uint32_t r = (c >> 16) & 0xFF;
        uint32_t g = (c >> 8)  & 0xFF;
        uint32_t b = (c >> 0)  & 0xFF;
        return (a << 24) | (b << 16) | (g << 8) | r;
    };

    const uint32_t NONE     = 0x00000000;
    const uint32_t WHITE    = Color(0xFFFFFF);
    const uint32_t BLACK    = Color(0x000000);
    const uint32_t GRAY50   = Color(0xFFFFFF);
    const uint32_t GRAY75   = Color(0xFDFDFD);
    const uint32_t GRAY100  = Color(0xF8F8F8);
    const uint32_t GRAY200  = Color(0xF4F4F4);
    const uint32_t GRAY300  = Color(0xEAEAEA);
    const uint32_t GRAY400  = Color(0xD3D3D3);
    const uint32_t GRAY500  = Color(0xBCBCBC);
    const uint32_t GRAY600  = Color(0x959595);
    const uint32_t GRAY700  = Color(0x767676);
    const uint32_t GRAY800  = Color(0x505050);
    const uint32_t GRAY900  = Color(0x323232);

    // Spectrum Accent Blues
    const uint32_t BLUE100  = Color(0xE5F0FF); // Light blue tint for readable headers
    const uint32_t BLUE200  = Color(0xCCE0FF);
    const uint32_t BLUE400  = Color(0x378EF0);
    const uint32_t BLUE500  = Color(0x2680EB);
    const uint32_t BLUE600  = Color(0x1473E6);
    const uint32_t BLUE700  = Color(0x0D66D0);

    ImVec4* colors = style->Colors;

    // Text
    colors[ImGuiCol_Text]                  = ColorConvertU32ToFloat4(GRAY800);
    colors[ImGuiCol_TextDisabled]          = ColorConvertU32ToFloat4(GRAY500);

    // Windows & Popups
    colors[ImGuiCol_WindowBg]              = ColorConvertU32ToFloat4(GRAY100);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]               = ColorConvertU32ToFloat4(GRAY50);
    colors[ImGuiCol_Border]                = ColorConvertU32ToFloat4(GRAY300);
    colors[ImGuiCol_BorderShadow]          = ColorConvertU32ToFloat4(NONE);

    // Frame Elements
    colors[ImGuiCol_FrameBg]               = ColorConvertU32ToFloat4(GRAY75);
    colors[ImGuiCol_FrameBgHovered]        = ColorConvertU32ToFloat4(GRAY50);
    colors[ImGuiCol_FrameBgActive]         = ColorConvertU32ToFloat4(GRAY200);

    // Title Bars & Menus
    colors[ImGuiCol_TitleBg]               = ColorConvertU32ToFloat4(GRAY300);
    colors[ImGuiCol_TitleBgActive]         = ColorConvertU32ToFloat4(GRAY200);
    colors[ImGuiCol_TitleBgCollapsed]      = ColorConvertU32ToFloat4(GRAY400);
    colors[ImGuiCol_MenuBarBg]             = ColorConvertU32ToFloat4(GRAY100);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg]           = ColorConvertU32ToFloat4(GRAY100);
    colors[ImGuiCol_ScrollbarGrab]         = ColorConvertU32ToFloat4(GRAY400);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ColorConvertU32ToFloat4(GRAY600);
    colors[ImGuiCol_ScrollbarGrabActive]   = ColorConvertU32ToFloat4(GRAY700);

    // Interactive Widgets
    colors[ImGuiCol_CheckMark]             = ColorConvertU32ToFloat4(BLUE500);
    colors[ImGuiCol_SliderGrab]            = ColorConvertU32ToFloat4(GRAY700);
    colors[ImGuiCol_SliderGrabActive]      = ColorConvertU32ToFloat4(GRAY800);
    colors[ImGuiCol_Button]                = ColorConvertU32ToFloat4(GRAY75);
    colors[ImGuiCol_ButtonHovered]         = ColorConvertU32ToFloat4(GRAY50);
    colors[ImGuiCol_ButtonActive]          = ColorConvertU32ToFloat4(GRAY200);

    // Headers & Selectables (Fixed Contrast)
    colors[ImGuiCol_Header]                = ColorConvertU32ToFloat4(BLUE100);
    colors[ImGuiCol_HeaderHovered]         = ColorConvertU32ToFloat4(BLUE200);
    colors[ImGuiCol_HeaderActive]          = ColorConvertU32ToFloat4(BLUE400);

    // Separators & Resizing
    colors[ImGuiCol_Separator]             = ColorConvertU32ToFloat4(GRAY400);
    colors[ImGuiCol_SeparatorHovered]      = ColorConvertU32ToFloat4(GRAY600);
    colors[ImGuiCol_SeparatorActive]       = ColorConvertU32ToFloat4(GRAY700);
    colors[ImGuiCol_ResizeGrip]            = ColorConvertU32ToFloat4(GRAY400);
    colors[ImGuiCol_ResizeGripHovered]     = ColorConvertU32ToFloat4(GRAY600);
    colors[ImGuiCol_ResizeGripActive]      = ColorConvertU32ToFloat4(GRAY700);

    // Tables (Fixed Missing Table Colors)
    colors[ImGuiCol_TableHeaderBg]         = ColorConvertU32ToFloat4(GRAY200);
    colors[ImGuiCol_TableBorderStrong]     = ColorConvertU32ToFloat4(GRAY400);
    colors[ImGuiCol_TableBorderLight]      = ColorConvertU32ToFloat4(GRAY300);
    colors[ImGuiCol_TableRowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]         = ColorConvertU32ToFloat4(GRAY75);

    // Tabs (Fixed Missing Tab Colors)
    colors[ImGuiCol_Tab]                   = ColorConvertU32ToFloat4(GRAY200);
    colors[ImGuiCol_TabHovered]            = ColorConvertU32ToFloat4(GRAY50);
    colors[ImGuiCol_TabActive]             = ColorConvertU32ToFloat4(GRAY100);
    colors[ImGuiCol_TabUnfocused]          = ColorConvertU32ToFloat4(GRAY200);
    colors[ImGuiCol_TabUnfocusedActive]    = ColorConvertU32ToFloat4(GRAY100);

    // Docking
    colors[ImGuiCol_DockingPreview]        = ColorConvertU32ToFloat4(BLUE400);
    colors[ImGuiCol_DockingEmptyBg]        = ColorConvertU32ToFloat4(GRAY100);

    // Plots & Misc
    colors[ImGuiCol_PlotLines]             = ColorConvertU32ToFloat4(BLUE400);
    colors[ImGuiCol_PlotLinesHovered]      = ColorConvertU32ToFloat4(BLUE600);
    colors[ImGuiCol_PlotHistogram]         = ColorConvertU32ToFloat4(BLUE400);
    colors[ImGuiCol_PlotHistogramHovered]  = ColorConvertU32ToFloat4(BLUE600);
    colors[ImGuiCol_TextSelectedBg]        = ColorConvertU32ToFloat4(Color(0x378EF0, 0x33));
    colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]          = ColorConvertU32ToFloat4(Color(0x323232, 0x1A));
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

/**
 * Credit to @TheAncientOwl for multiple themes
 * https://github.com/ocornut/imgui/issues/707#issuecomment-4107169777
 */
void theme_forest_green()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.85f, 0.90f, 0.85f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.50f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.09f, 0.06f, 1.00f); // Deep pine
    colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.11f, 0.08f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.10f, 0.07f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.18f, 0.28f, 0.18f, 0.80f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, Checkboxes, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.18f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.30f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.42f, 0.24f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.14f, 0.09f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.26f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.08f, 0.05f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.14f, 0.09f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.08f, 0.05f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.18f, 0.28f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.38f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.32f, 0.48f, 0.32f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.45f, 0.75f, 0.45f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.55f, 0.35f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.70f, 0.45f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.18f, 0.35f, 0.18f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.45f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.32f, 0.55f, 0.32f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.18f, 0.35f, 0.18f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.45f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.32f, 0.55f, 0.32f, 1.00f);

    // Separators and Resizing
    colors[ImGuiCol_Separator] = ImVec4(0.18f, 0.28f, 0.18f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.25f, 0.45f, 0.25f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.55f, 0.32f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.18f, 0.35f, 0.18f, 0.80f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.45f, 0.25f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.32f, 0.55f, 0.32f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.22f, 0.12f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.45f, 0.25f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.38f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.15f, 0.08f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.22f, 0.12f, 1.00f);

    // Plots
    colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.70f, 0.40f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.50f, 0.85f, 0.50f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.70f, 0.40f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.50f, 0.85f, 0.50f, 1.00f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.12f, 0.22f, 0.12f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.35f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.15f, 0.25f, 0.15f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.08f, 0.14f, 0.08f, 0.50f);

    // Misc
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 0.55f, 0.25f, 0.50f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.60f, 0.90f, 0.60f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.40f, 0.80f, 0.40f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.85f, 0.90f, 0.85f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.10f, 0.15f, 0.10f, 0.50f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.08f, 0.05f, 0.60f);
}

void theme_amethyst()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.50f, 0.60f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.07f, 0.12f, 1.00f); // Deep charcoal-purple
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.09f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.07f, 0.12f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.20f, 0.35f, 0.80f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, Checkboxes, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.12f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.20f, 0.38f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.25f, 0.55f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.09f, 0.18f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.14f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.05f, 0.10f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.09f, 0.18f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.05f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.20f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.30f, 0.50f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.45f, 0.40f, 0.65f, 1.00f);

    // Interactables (The "Pop" colors)
    colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.45f, 0.95f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.35f, 0.75f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.65f, 0.45f, 0.95f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.20f, 0.40f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.28f, 0.62f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.35f, 0.80f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.25f, 0.20f, 0.40f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.28f, 0.62f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.35f, 0.80f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.12f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.28f, 0.62f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.20f, 0.45f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.08f, 0.15f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.12f, 0.25f, 1.00f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.18f, 0.15f, 0.28f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.25f, 0.20f, 0.40f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.15f, 0.30f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);

    // Misc
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.50f, 0.35f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.80f, 0.65f, 1.00f, 0.95f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.45f, 0.90f, 1.00f);
}

void theme_sapphire()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.93f, 0.97f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.50f, 0.65f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.09f, 0.12f, 1.00f); // Deep midnight
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.12f, 0.16f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.09f, 0.12f, 0.95f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.15f, 0.25f, 0.35f, 0.70f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, Checkboxes, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.18f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.28f, 0.40f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.38f, 0.55f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.22f, 0.35f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.08f, 0.12f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.16f, 0.22f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.08f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.32f, 0.48f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.42f, 0.60f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.50f, 0.75f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.55f, 0.85f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.75f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.18f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.48f, 0.75f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.60f, 0.90f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.18f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.48f, 0.75f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.60f, 0.90f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.20f, 0.32f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.45f, 0.70f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.20f, 0.32f, 1.00f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.15f, 0.25f, 0.40f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.15f, 0.25f, 0.40f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.05f);

    // Misc
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.55f, 0.85f, 0.40f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.50f, 0.80f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.40f, 0.70f, 1.00f, 1.00f);
}

void theme_amber_yellow()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(1.00f, 0.95f, 0.80f, 1.00f); // Soft cream-yellow
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.45f, 0.30f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.06f, 1.00f); // Near black
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.08f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.06f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.30f, 0.25f, 0.10f, 0.80f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, Checkboxes, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.14f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.22f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.30f, 0.15f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.11f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.18f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.04f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.11f, 0.08f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.04f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.35f, 0.30f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.45f, 0.40f, 0.15f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.55f, 0.50f, 0.20f, 1.00f);

    // Interactables (The High-Vis Amber)
    colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.80f, 0.10f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.60f, 0.10f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.95f, 0.80f, 0.10f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.30f, 0.25f, 0.05f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.45f, 0.38f, 0.10f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.60f, 0.50f, 0.15f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.30f, 0.25f, 0.05f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.38f, 0.10f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.60f, 0.50f, 0.15f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.14f, 0.10f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.38f, 0.10f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.30f, 0.10f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.07f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.14f, 0.10f, 1.00f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.18f, 0.16f, 0.10f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.35f, 0.30f, 0.15f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.25f, 0.20f, 0.10f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.03f);

    // Misc
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.95f, 0.80f, 0.10f, 0.25f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.85f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.95f, 0.80f, 0.10f, 1.00f);
}

void theme_dracula()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Dracula Color Palette
    // Background: #282a36 | Selection: #44475a | Foreground: #f8f8f2
    // Comment: #6272a4    | Cyan: #8be9fd      | Green: #50fa7b
    // Orange: #ffb86c     | Pink: #ff79c6      | Purple: #bd93f9
    // Red: #ff5555        | Yellow: #f1fa8c

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.97f, 0.97f, 0.95f, 1.00f); // #f8f8f2
    colors[ImGuiCol_TextDisabled] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f); // #6272a4

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f); // #282a36
    colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.16f, 0.21f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.21f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f); // #44475a
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f); // #44475a
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f); // #6272a4
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f); // Darker
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.31f, 0.98f, 0.48f, 1.00f); // #50fa7b (Green)
    colors[ImGuiCol_SliderGrab] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f); // #bd93f9 (Purple)
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.84f, 0.68f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.47f, 0.78f, 1.00f); // #ff79c6 (Pink)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.37f, 0.62f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);

    // Misc
    colors[ImGuiCol_PlotLines] = ImVec4(0.55f, 0.91f, 0.99f, 1.00f); // #8be9fd (Cyan)
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f);
}

void theme_catppuccin_mocha()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;


    // Catppuccin Mocha Palette
    // Base: #1e1e2e | Mantle: #181825 | Crust: #11111b
    // Text: #cdd6f4 | Subtext0: #a6adc8 | Surface0: #313244
    // Lavender: #b4befe | Sapphire: #74c7ec | Mauve: #cba6f7

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.80f, 0.84f, 0.96f, 1.00f); // Text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.42f, 0.45f, 0.55f, 1.00f); // Surface1

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f); // Base
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f); // Mantle
    colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.11f, 0.96f); // Crust

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f); // Surface0
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames (Inputs, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f); // Surface0
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.26f, 0.35f, 1.00f); // Surface1
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f); // Surface2

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f); // Mantle
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f); // Base
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.11f, 1.00f); // Crust

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f); // Surface2
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.37f, 0.38f, 0.51f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.42f, 0.45f, 0.55f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.75f, 1.00f, 1.00f); // Lavender
    colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.78f, 0.93f, 1.00f); // Sapphire
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.78f, 0.93f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.65f, 0.97f, 1.00f); // Mauve
    colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.55f, 0.87f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.26f, 0.35f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);

    // Misc
    colors[ImGuiCol_PlotLines] = ImVec4(0.94f, 0.72f, 0.42f, 1.00f); // Marigold
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.71f, 0.75f, 1.00f, 1.00f); // Lavender
}

void theme_gruvbox_hard()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Gruvbox Dark Hard Palette
    // Background: #1d2021 (Dark Hard) | Foreground: #ebdbb2
    // Red: #fb4934 | Green: #b8bb26 | Yellow: #fabd2f | Blue: #83a598
    // Gray: #928374 | Orange: #fe8019

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.86f, 0.70f, 1.00f); // #ebdbb2
    colors[ImGuiCol_TextDisabled] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f); // #928374

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f); // #1d2021
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.95f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames
    colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f); // #3c3836
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f); // #665c54

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.14f, 0.13f, 1.00f); // #282828

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.72f, 0.73f, 0.15f, 1.00f); // #b8bb26 (Green)
    colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.65f, 0.60f, 1.00f); // #83a598 (Blue)
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.73f, 0.67f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f); // #fb4934 (Red)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.20f, 0.15f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);

    // Misc
    colors[ImGuiCol_PlotLines] = ImVec4(0.98f, 0.74f, 0.18f, 1.00f); // #fabd2f (Yellow)
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f);
}

void theme_crimson_vesuvius()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(1.00f, 0.90f, 0.90f, 1.00f); // Slight pinkish tint to off-white
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.40f, 0.40f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.07f, 0.07f, 1.00f); // Deep charcoal
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.09f, 0.09f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.07f, 0.07f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.15f, 0.15f, 0.80f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.20f, 0.20f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.08f, 0.08f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.45f, 0.20f, 0.20f, 1.00f);

    // Interactables (The High-Intensity Red)
    colors[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.15f, 0.15f, 1.00f); // Sharp Red
    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.30f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.30f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.50f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.70f, 0.25f, 0.25f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.50f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.12f, 0.12f, 1.00f);

    // Misc
    colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.85f, 0.15f, 0.15f, 0.35f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);
}

void theme_rose_quartz()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.90f, 0.95f, 1.00f); // Soft white-pink
    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.45f, 0.55f, 1.00f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.10f, 0.12f, 1.00f); // Deep Plum-Grey
    colors[ImGuiCol_ChildBg] = ImVec4(0.14f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.08f, 0.10f, 0.96f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.35f, 0.25f, 0.35f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.15f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.22f, 0.30f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.28f, 0.40f, 1.00f);

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.10f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.15f, 0.25f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.06f, 0.08f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.10f, 0.15f, 1.00f);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.06f, 0.08f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.25f, 0.40f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.55f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.45f, 0.70f, 1.00f);

    // Interactables (The Rose Pop)
    colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.60f, 0.75f, 1.00f); // Rose Pink
    colors[ImGuiCol_SliderGrab] = ImVec4(0.85f, 0.50f, 0.65f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.95f, 0.60f, 0.75f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.45f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.65f, 0.35f, 0.50f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.85f, 0.45f, 0.65f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.45f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.55f, 0.30f, 0.45f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.65f, 0.35f, 0.55f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.15f, 0.20f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.65f, 0.35f, 0.50f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.45f, 0.25f, 0.35f, 1.00f);

    // Misc
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.95f, 0.60f, 0.75f, 0.35f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.95f, 0.60f, 0.75f, 1.00f);

#ifdef IMGUI_HAS_DOCK
    colors[ImGuiCol_DockingPreview] = ImVec4(0.95f, 0.60f, 0.75f, 0.40f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.12f, 0.10f, 0.12f, 1.00f);
#endif
}

std::vector<std::function<void()>> theme_functions{theme_dark, theme_light, theme_classic,
                                                  theme_spectrum, theme_forest_green, theme_amethyst, theme_sapphire, theme_amber_yellow, theme_crimson_vesuvius, theme_rose_quartz, theme_dracula, theme_catppuccin_mocha, theme_gruvbox_hard};

std::vector<const char*> theme_names{"Dark", "Light", "Classic", "Spectrum", "Forest Green", "Amethyst", "Sapphire", "Amber Yellow", "Crimson Vesuvius", "Rose Quartz", "Dracula", "Catppuccin Mocha", "Gruvbox Hard"};

#endif
