#ifndef XCGE_IMGUI_BINDINGS_HPP
#define XCGE_IMGUI_BINDINGS_HPP

#include "imgui.h"

#include <string>
// Ported from XCGE game engine

//#include "renderer/texture.h"

namespace ImGui {

struct InputTextCallback_UserData {
  std::string *Str;
  ImGuiInputTextCallback ChainCallback;
  void *ChainCallbackUserData;
};
// Todo: Add parameters to change the UVs
// Imgui Image Button with native xcge::Texture textures
// bool ImageButton(const xcge::Texture& texture,ImVec2 size = ImVec2(0.f,0.f));
// void Image(const xcge::Texture& texture,ImVec2 size = ImVec2(0.f,0.f));
// Imgui InputText with stl strings

bool InputText(const char *label,
               std::string &strRef,
               ImGuiInputTextFlags flags       = 0,
               ImGuiInputTextCallback callback = nullptr,
               void *user_data                 = nullptr);
bool InputTextMultiline(const char *label,
                        std::string &strRef,
                        const ImVec2 &size              = ImVec2(0, 0),
                        ImGuiInputTextFlags flags       = 0,
                        ImGuiInputTextCallback callback = nullptr,
                        void *user_data                 = nullptr);

} // namespace ImGui

#endif // XCGE_IMGUI_BINDINGS_HPP
