#include "sdl2_backend.hpp"

namespace xhfr {
bool done = false;
SDL_Window* g_Window = NULL;
SDL_GLContext g_GLContext = NULL;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
const char* glsl_version = "#version 100";

bool backend_init(const char* appName, int w, int h) {
  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  // For the browser using Emscripten, we are going to use WebGL1 with GL ES2.
  // See the Makefile. for requirement details. It is very likely the generated
  // file won't work in many browsers. Firefox is the only sure bet, but I have
  // successfully run this code on Chrome for Android for example.

  // const char* glsl_version = "#version 300 es";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  g_Window =
      SDL_CreateWindow("Dear ImGui Emscripten example", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  g_GLContext = SDL_GL_CreateContext(g_Window);
  if (!g_GLContext) {
    fprintf(stderr, "Failed to initialize WebGL context!\n");
    return 1;
  }

  return true;
}

void backend_render() {
  ImGui::Render();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(g_Window);
}
void backend_new_frame() {
  SDL_Event event;

  while (SDL_PollEvent(&event))

  {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)

      done = true;

    if (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(g_Window))

      done = true;
  }
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(g_Window);
}
void backend_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  SDL_GL_DeleteContext(g_GLContext);
  SDL_DestroyWindow(g_Window);
  SDL_Quit();
}
bool backend_should_close() {
  return done;
}

bool backend_viewports_support() {
  return 0;
}

void backend_init_platform_impl() {
  ImGui_ImplSDL2_InitForOpenGL(g_Window, g_GLContext);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

}  // namespace xhfr
