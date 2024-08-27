#include "Styles.hpp"
#include "imgui.h"

void xhfr::styles::SyleModern() {
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();


    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 1.0;
    style.DisabledAlpha = 0.6000000238418579;
    style.WindowPadding = ImVec2(4.0, 6.0);
    style.WindowRounding = 0.0;
    style.WindowBorderSize = 0.0;
    style.WindowMinSize = ImVec2(32.0, 32.0);
    style.WindowTitleAlign = ImVec2(0.0, 0.5);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 5.0;
    style.ChildBorderSize = 1.0;
    style.PopupRounding = 5.0;
    style.PopupBorderSize = 1.0;
    style.FramePadding = ImVec2(8.0, 6.0);
    style.FrameRounding = 5.0;
    style.FrameBorderSize = 1.0;
    style.ItemSpacing = ImVec2(8.0, 6.0);
    style.ItemInnerSpacing = ImVec2(8.0, 6.0);
    style.CellPadding = ImVec2(4.0, 2.0);
    style.IndentSpacing = 20.0;
    style.ColumnsMinSpacing = 6.0;
    style.ScrollbarSize = 20.0;
    style.ScrollbarRounding = 0.0;
    style.GrabMinSize = 5.0;
    style.GrabRounding = 5.0;
    style.TabRounding = 4.0;
    style.TabBorderSize = 0.0;
    style.TabMinWidthForCloseButton = 0.0;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.SelectableTextAlign = ImVec2(0.0, 0.0);


    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.13f, 0.13f, 0.13f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(1.00f, 0.00f, 1.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 0.15f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
}


void xhfr::styles::SyleRetroX() {
    ImGuiStyle& mStyle = ImGui::GetStyle();
    mStyle.WindowMinSize = ImVec2(160, 20);
    mStyle.FramePadding = ImVec2(5, 4);
    mStyle.WindowPadding = ImVec2(10, 10);
    mStyle.ItemSpacing = ImVec2(5, 4);
    mStyle.FrameRounding = 3.0f;
    mStyle.IndentSpacing = 16.0f;
    mStyle.GrabRounding = 3.0f;
    mStyle.ScrollbarSize = 12.0f;
    mStyle.ScrollbarRounding = 3.0f;

    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 1.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.56f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.32f, 0.00f, 0.41f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.16f, 0.00f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.29f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.48f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.00f, 0.00f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.31f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.94f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.86f, 0.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.00f, 0.44f, 0.00f, 0.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.47f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.42f, 0.00f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 0.00f, 0.11f);

    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.43f, 0.00f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.00f, 0.72f, 0.00f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.91f, 0.00f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.81f, 0.00f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.46f, 0.00f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.35f, 0.00f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.59f, 0.00f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00f, 0.34f, 0.00f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.59f, 0.00f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.20f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 0.61f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.87f, 0.00f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.00f, 1.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.00f, 0.80f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.80f, 0.00f, 0.35f);

    // set rounding and borders
    style->ChildRounding = 0;
    style->FrameRounding = 0;
    style->GrabRounding = 0;
    style->PopupRounding = 0;
    style->ScrollbarRounding = 0;
    style->TabRounding = 0;
    style->WindowRounding = 0;

    style->ChildBorderSize = 1;
    style->FrameBorderSize = 1;
    style->PopupBorderSize = 1;
    style->TabBorderSize = 1;
    style->WindowBorderSize = 1;
}


void xhfr::styles::StyleDefault() {
  ImGuiStyle& mStyle = ImGui::GetStyle();
  mStyle.WindowMinSize = ImVec2(160, 20);
  mStyle.WindowPadding = ImVec2(10, 10);
  mStyle.PopupRounding = 0.0f;
  mStyle.FramePadding = ImVec2(10, 4);
  mStyle.ItemSpacing = ImVec2(10, 4);
  mStyle.ItemInnerSpacing = ImVec2(4, 4);
  mStyle.IndentSpacing = 18.0f;
  mStyle.ScrollbarSize = 18.0f;
  mStyle.GrabMinSize = 6.0f;

  mStyle.WindowBorderSize = 1.0f;
  mStyle.ChildBorderSize = 2.0f;
  mStyle.PopupBorderSize = 1.0f;
  mStyle.FrameBorderSize = 0.0f;
  mStyle.TabBorderSize = 0.0f;

  mStyle.WindowRounding = 0.0f;
  mStyle.ChildRounding = 0.0f;
  mStyle.FrameRounding = 0.0f;
  mStyle.ScrollbarRounding = 0.0f;
  mStyle.GrabRounding = 0.0f;
  mStyle.TabRounding = 0.0f;

  mStyle.WindowTitleAlign = ImVec2(0.5f, 0.5f);

  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 0.00f, 1.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
}
