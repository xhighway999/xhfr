#include "xhfr.hpp"

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow *xhfr::window;
xhfr::WindowManagerBase *xhfr::wm;
xhfr::Dockspace xhfr::dockspace;

void setupTheme() {
  /*ImGuiStyle &mStyle       = ImGui::GetStyle();
  mStyle.WindowMinSize     = ImVec2(160, 20);
  mStyle.FramePadding      = ImVec2(5, 4);
  mStyle.WindowPadding     = ImVec2(10, 10);
  mStyle.ItemSpacing       = ImVec2(5, 4);
  mStyle.FrameRounding     = 3.0f;
  mStyle.IndentSpacing     = 16.0f;
  mStyle.GrabRounding      = 3.0f;
  mStyle.ScrollbarSize     = 12.0f;
  mStyle.ScrollbarRounding = 3.0f;

  ImGuiStyle *style                      = &ImGui::GetStyle();
  ImVec4 *colors                         = style->Colors;
  colors[ImGuiCol_Text]                  = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]          = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
  colors[ImGuiCol_WindowBg]              = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
  colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 1.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
  colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
  colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.56f);
  colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.00f, 0.32f, 0.00f, 0.41f);
  colors[ImGuiCol_FrameBgActive]         = ImVec4(0.00f, 0.16f, 0.00f, 0.67f);
  colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
  colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.29f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.48f);
  colors[ImGuiCol_MenuBarBg]             = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.00f, 0.00f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.00f, 0.31f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_CheckMark]             = ImVec4(0.00f, 0.94f, 0.00f, 1.00f);
  colors[ImGuiCol_SliderGrab]            = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.00f, 0.86f, 0.00f, 1.00f);
  colors[ImGuiCol_Button]                = ImVec4(0.00f, 0.44f, 0.00f, 0.00f);
  colors[ImGuiCol_ButtonHovered]         = ImVec4(0.00f, 0.47f, 0.00f, 1.00f);
  colors[ImGuiCol_ButtonActive]          = ImVec4(0.00f, 0.42f, 0.00f, 1.00f);
  colors[ImGuiCol_Header]                = ImVec4(0.00f, 0.70f, 0.00f, 0.00f);
  colors[ImGuiCol_HeaderHovered]         = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
  colors[ImGuiCol_HeaderActive]          = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
  colors[ImGuiCol_Separator]             = ImVec4(0.00f, 0.43f, 0.00f, 0.50f);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.00f, 0.72f, 0.00f, 0.78f);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.00f, 0.51f, 0.00f, 1.00f);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.91f, 0.00f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.00f, 0.81f, 0.00f, 0.67f);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.00f, 0.46f, 0.00f, 0.95f);
  colors[ImGuiCol_Tab]                   = ImVec4(0.00f, 0.35f, 0.00f, 0.86f);
  colors[ImGuiCol_TabHovered]            = ImVec4(0.00f, 0.59f, 0.00f, 0.80f);
  colors[ImGuiCol_TabActive]             = ImVec4(0.00f, 0.41f, 0.00f, 1.00f);
  colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
  colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.00f, 0.34f, 0.00f, 1.00f);
  colors[ImGuiCol_DockingPreview]        = ImVec4(0.00f, 0.59f, 0.00f, 0.70f);
  colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.00f, 0.20f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLines]             = ImVec4(0.00f, 0.61f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.00f, 0.43f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.87f, 0.00f, 0.35f);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(0.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight]          = ImVec4(0.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.00f, 1.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.00f, 0.80f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.00f, 0.80f, 0.00f, 0.35f);

  // set rounding and borders
  style->ChildRounding     = 0;
  style->FrameRounding     = 0;
  style->GrabRounding      = 0;
  style->PopupRounding     = 0;
  style->ScrollbarRounding = 0;
  style->TabRounding       = 0;
  style->WindowRounding    = 0;

  style->ChildBorderSize  = 1;
  style->FrameBorderSize  = 1;
  style->PopupBorderSize  = 1;
  style->TabBorderSize    = 1;
  style->WindowBorderSize = 1;*/
  ImGuiStyle &mStyle      = ImGui::GetStyle();
  mStyle.WindowMinSize    = ImVec2(160, 20);
  mStyle.WindowPadding    = ImVec2(10, 10);
  mStyle.PopupRounding    = 0.0f;
  mStyle.FramePadding     = ImVec2(10, 4);
  mStyle.ItemSpacing      = ImVec2(10, 4);
  mStyle.ItemInnerSpacing = ImVec2(4, 4);
  mStyle.IndentSpacing    = 18.0f;
  mStyle.ScrollbarSize    = 18.0f;
  mStyle.GrabMinSize      = 6.0f;

  mStyle.WindowBorderSize = 1.0f;
  mStyle.ChildBorderSize  = 2.0f;
  mStyle.PopupBorderSize  = 1.0f;
  mStyle.FrameBorderSize  = 0.0f;
  mStyle.TabBorderSize    = 0.0f;

  mStyle.WindowRounding    = 0.0f;
  mStyle.ChildRounding     = 0.0f;
  mStyle.FrameRounding     = 0.0f;
  mStyle.ScrollbarRounding = 0.0f;
  mStyle.GrabRounding      = 0.0f;
  mStyle.TabRounding       = 0.0f;

  mStyle.WindowTitleAlign = ImVec2(0.5f, 0.5f);

  ImVec4 *colors                         = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]          = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_WindowBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
  colors[ImGuiCol_PopupBg]               = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_Border]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
  colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_FrameBgActive]         = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_MenuBarBg]             = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_CheckMark]             = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
  colors[ImGuiCol_SliderGrab]            = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_Button]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_ButtonHovered]         = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_ButtonActive]          = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
  colors[ImGuiCol_Header]                = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_HeaderHovered]         = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_HeaderActive]          = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
  colors[ImGuiCol_Separator]             = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_Tab]                   = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_TabHovered]            = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors[ImGuiCol_TabActive]             = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
  colors[ImGuiCol_TabUnfocused]          = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_DockingPreview]        = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
  colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_NavHighlight]          = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
  colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.43f);
}

int xhfr::init(const char *appName) {
  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  if(!glfwInit())
    return 1;

    // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  // Create window with graphics context
  window = glfwCreateWindow(1280, 720, appName, NULL, NULL);
  if(window == NULL)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
  bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  bool err = gladLoadGL() == 0;
#else
  bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader
                    // is likely to requires some form of initialization.
#endif
  if(err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport /
                                                      // Platform Windows
  // io.ConfigViewportsNoAutoMerge = true;
  // io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle &style = ImGui::GetStyle();
  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding              = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can
  // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
  // them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
  // need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please
  // handle those errors in your application (e.g. use an assertion, or display
  // an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored
  // into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
  // ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'misc/fonts/README.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string
  // literal you need to write a double backslash \\ !
  // io.Fonts->AddFontDefault();
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  // ImFont* font =
  // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
  // NULL, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

  setupTheme();
  // allocate the window manager
  wm = new WindowManagerImpl();
  return 0;
}

int xhfr::main() {
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // Main loop
  while(!glfwWindowShouldClose(window)) {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application. Generally you may always pass all inputs
    // to dear imgui, and hide them from your application based on those two
    // flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    dockspace.dockspaceStart();
    dockspace.dockspaceEnd();

    wm->manageWindows();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we
    // save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call
    //  glfwMakeContextCurrent(window) directly)
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow *backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  delete wm;

  return 0;
}
