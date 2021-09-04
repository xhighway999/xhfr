#pragma once

#include <stdio.h>

#include <string>

#include "widgets/Bezier.hpp"

#include "imgui.h"
namespace ImGui {
void AutoPlot(const char* label,
              float* newValue,
              float* values,
              int values_count,
              const char* overlay_text = NULL,
              float scale_min = FLT_MAX,
              float scale_max = FLT_MAX,
              ImVec2 graph_size = ImVec2(0, 0),
              int stride = sizeof(float));

struct InputTextCallback_UserData {
  std::string* Str;
  ImGuiInputTextCallback ChainCallback;
  void* ChainCallbackUserData;
};

void Link(const char* linkText,
          const char* link = nullptr,
          ImColor color = ImColor(0, 0, 255));

bool InputText(const char* label,
               std::string& strRef,
               ImGuiInputTextFlags flags = 0,
               ImGuiInputTextCallback callback = nullptr,
               void* user_data = nullptr);
bool InputTextMultiline(const char* label,
                        std::string& strRef,
                        const ImVec2& size = ImVec2(0, 0),
                        ImGuiInputTextFlags flags = 0,
                        ImGuiInputTextCallback callback = nullptr,
                        void* user_data = nullptr);

}  // namespace ImGui
