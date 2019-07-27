#include "sdl2_backend.hpp"

namespace xhfr {
bool done = false;
SDL_Window *window;
SDL_GLContext gl_context;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool backend_init(const char *appName) {
  // Setup SDL
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
    printf("Error: %s\n", SDL_GetError());
    return false;
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 Core + GLSL 150
  const char *glsl_version = "#version 150";
  SDL_GL_SetAttribute(
      SDL_GL_CONTEXT_FLAGS,
      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window     = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1280,
                            720,
                            window_flags);
  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

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
    return false;
  }

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);
  return true;
}

void backend_render() {
  ImGui::Render();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows

  // (Platform functions may change the current OpenGL context, so we
  // save/restore it to make it easier to paste this code elsewhere.

  //  For this specific demo app we could also call SDL_GL_MakeCurrent(window,
  //  gl_context) directly)

  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)

  {
    SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();

    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

    ImGui::UpdatePlatformWindows();

    ImGui::RenderPlatformWindowsDefault();

    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  SDL_GL_SwapWindow(window);
}
void backend_new_frame() {
  SDL_Event event;

  while(SDL_PollEvent(&event))

  {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if(event.type == SDL_QUIT)

      done = true;

    if(event.type == SDL_WINDOWEVENT &&
       event.window.event == SDL_WINDOWEVENT_CLOSE &&
       event.window.windowID == SDL_GetWindowID(window))

      done = true;
  }
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
}
void backend_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
bool backend_should_close() {
  return done;
}

} // namespace xhfr
