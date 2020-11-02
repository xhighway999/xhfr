#include "glfw_backend.hpp"

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void gl_error_callback(GLenum source,
                       GLenum type,
                       GLuint id,
                       GLenum severity,
                       GLsizei length,
                       const GLchar* message,
                       const void* userParam) {
  const char* severityString = "invalid";
#define STRTOENUM(strname, valname) \
  case valname:                     \
    strname = #valname;             \
    break;

  switch (severity) {
    STRTOENUM(severityString, GL_DEBUG_SEVERITY_HIGH)
    STRTOENUM(severityString, GL_DEBUG_SEVERITY_MEDIUM)
    STRTOENUM(severityString, GL_DEBUG_SEVERITY_LOW)
    STRTOENUM(severityString, GL_DEBUG_SEVERITY_NOTIFICATION)
  }

  char debugMessage[1024];
  sprintf(debugMessage, "GL CALLBACK: %s type = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, message);

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      XHFR_ERROR("{}", debugMessage);
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:

      XHFR_WARN("{}", debugMessage);
      break;
    case GL_DEBUG_SEVERITY_LOW:

      XHFR_INFO("{}", debugMessage);
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      XHFR_DEBUG("{}", debugMessage);
      break;
    default:
      throw 1;
  }
}

namespace xhfr {
GLFWwindow* window;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
const char* glsl_version = 0;
bool backend_init(const char* appName, int w, int h) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
#else
  // GL 3.0 + GLSL 130
  glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  // Create window with graphics context
  window = glfwCreateWindow(w, h, appName, NULL, NULL);
  if (window == NULL)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);  // Disable vsync

  // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
  bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  bool err = gladLoadGL() == 0;
#else
  bool err = false;  // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader
                     // is likely to requires some form of initialization.
#endif
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return false;
  }
  return true;
}

void backend_init_platform_impl() {
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  glDebugMessageCallback(gl_error_callback, NULL);
}

void backend_render() {
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

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
  glfwSwapBuffers(window);
}

void backend_new_frame() {
  glfwPollEvents();
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
}
void backend_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool backend_should_close() {
  return glfwWindowShouldClose(window);
}

bool backend_viewports_support() {
  return 1;
}

}  // namespace xhfr
