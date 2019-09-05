#pragma once
#include "imgui.h"

// About OpenGL function loaders: modern OpenGL doesn't have a standard header
// file and requires individual function pointers to be loaded manually. Helper
// libraries are often used for this purpose! Here we are supporting a few
// common ones: gl3w, glew, glad. You may use another loader/header of your
// choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>  // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>  // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_SDL_GL2)
#include <GLES3/gl3.h>
#include <SDL_opengles2.h>
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "backend_keycodes.hpp"

namespace xhfr {
bool backend_init(const char* appName = "xhfr", int w = 1270, int h = 800);
void backend_render();
void backend_new_frame();
void backend_shutdown();
bool backend_should_close();
bool backend_viewports_support();
}  // namespace xhfr
