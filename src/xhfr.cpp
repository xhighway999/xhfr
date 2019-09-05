#include "xhfr.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

void emscripten_main_loop(void* arg) {
  xhfr::new_frame();
}

#endif

xhfr::WindowManagerBase* xhfr::wm;
xhfr::Dockspace xhfr::dockspace;

void setupTheme() {
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
  colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
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
  colors[ImGuiCol_Header] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
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

int xhfr::init(int argc, char* argv[], const char* appName, int w, int h) {
  // Setup Dear ImGui context
  xhfr::fs::init(argv[0]);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
  // io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (backend_viewports_support())
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer bindings
  if (!backend_init(appName, w, h)) {
    return -1;
  }

  setupTheme();
  // allocate the window manager
  wm = new WindowManagerImpl();
  return 0;
}

void xhfr::new_frame() {
  backend_new_frame();
  ImGui::NewFrame();
  dockspace.dockspaceStart();
  dockspace.dockspaceEnd();
  wm->manageWindows();

  backend_render();
}

int xhfr::main() {
  FontManager::getInstance().build();
  // Main loop
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(emscripten_main_loop, NULL, 0, true);
#else
  while (!backend_should_close()) {
    new_frame();
  }
  backend_shutdown();
  ImGui::DestroyContext();

  delete wm;
#endif
  return 0;
}

void xhfr::shutdown() {
  xhfr::fs::shutdown();
}
