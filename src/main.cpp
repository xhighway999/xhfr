/*// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui/imgui.h"
#include "imgui_impl/imgui_impl_glfw.h"
#include "imgui_impl/imgui_impl_opengl3.h"
#include <stdio.h>

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually.
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "FilterApp.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


void setupTheme()
{
    ImGuiStyle &mStyle       = ImGui::GetStyle();
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
  style->WindowBorderSize = 1;
}


int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
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
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    FilterApp app;
    setupTheme();
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        app.OnRun();
        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
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

    return 0;
}
*/
/*
extern "C" {

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luajit/src/luajit.h>
}*/

#include <lua.hpp>

int main(int argc, char *argv[])
{
  int status;
  lua_State *L;
  
  L = luaL_newstate(); // open Lua
  if (!L) {
    return -1; // Checks that Lua started up
  }
  
  luaL_openlibs(L); // load Lua libraries
  if (argc > 1) {
    status = luaL_loadfile(L, argv[1]);  // load Lua script
    lua_call(L, 0, 0); // tell Lua to run the script
  }

  lua_close(L); // Close Lua
  return 0;
}
