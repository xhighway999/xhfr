#include "xhfr.hpp"

#ifdef __EMSCRIPTEN__
void emscripten_main_loop(void* arg) {
  xhfr::new_frame();
}

#endif

xhfr::WindowManagerBase* xhfr::wm;
xhfr::Dockspace xhfr::dockspace;
std::vector<std::function<void()>> xhfr::userOnFrameFunctions;
xhfr::debug xhfr::dbg;

int xhfr::init(int argc, char* argv[], const char* appName, int w, int h) {
  dbg.initLogging();
  if (argc != 0) {
    xhfr::fs::init(argv[0]);
  } else {
    xhfr::fs::init(nullptr);
  }

  // Setup Platform/Renderer bindings
  if (!backend_init(appName, w, h)) {
    return -1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
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
  backend_init_platform_impl();

  xhfr::styles::StyleDefault();
  // allocate the window manager
  wm = new WindowManagerImpl();
  backend_set_drag_drop_callback(wm->getDropEventCallback());
  return 0;
}

void xhfr::new_frame() {
  backend_new_frame();
  ImGui::NewFrame();
  dockspace.viewportHasWindowBar = wm->MainMenuBarUsed();
  dockspace.dockspaceStart();
  dockspace.dockspaceEnd();
  wm->manageWindows();

  // execute user on frame functions
  for (auto& user_funcs : userOnFrameFunctions) {
    user_funcs();
  }

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
  shutdown();
#endif
  return 0;
}

void xhfr::shutdown() {
  backend_shutdown();
  ImGui::DestroyContext();

  delete wm;

  xhfr::fs::shutdown();
}

void xhfr::addUserFunction(const std::function<void()> func) {
  userOnFrameFunctions.push_back(func);
}
