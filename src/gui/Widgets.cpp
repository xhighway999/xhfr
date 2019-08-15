#include "Widgets.hpp"

void ImGui::AutoPlot(const char* label,
                     float* newValue,
                     float* values,
                     int values_count,
                     const char* overlay_text,
                     float scale_min,
                     float scale_max,
                     ImVec2 graph_size,
                     int stride) {
  ImGui::PushID(label);

  ImGuiID refreshTimeId = ImGui::GetID("refresh_time");
  ImGuiID valuesOffsetId = ImGui::GetID("values_offset");
  double refresh_time =
      ImGui::GetStateStorage()->GetFloat(refreshTimeId, ImGui::GetTime());
  if (refresh_time == 0.0)
    refresh_time = ImGui::GetTime();

  int values_offset = ImGui::GetStateStorage()->GetInt(valuesOffsetId, 0);
  while (refresh_time < ImGui::GetTime()) {
    values[values_offset] = *newValue;
    values_offset = (values_offset + 1) % values_count;
    refresh_time += 1.0f / 60.0f;
  }
  ImGui::PlotLines(label, values, values_count, values_offset, overlay_text,
                   scale_min, scale_max, graph_size, stride);
  ImGui::SameLine();
  ImGui::Text("%f", values[values_offset - 1]);
  ImGui::GetStateStorage()->SetFloat(refreshTimeId, refresh_time);
  ImGui::GetStateStorage()->SetInt(valuesOffsetId, values_offset);
  ImGui::PopID();
}

static int InputTextCallback(ImGuiInputTextCallbackData* data) {
  ImGui::InputTextCallback_UserData* user_data =
      (ImGui::InputTextCallback_UserData*)data->UserData;
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    // Resize string callback
    std::string* str = user_data->Str;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char*)str->c_str();
  } else if (user_data->ChainCallback) {
    // Forward to user callback, if any
    data->UserData = user_data->ChainCallbackUserData;
    return user_data->ChainCallback(data);
  }
  return 0;
}

bool ImGui::InputText(const char* label,
                      std::string& strRef,
                      ImGuiInputTextFlags flags,
                      ImGuiInputTextCallback callback,
                      void* user_data) {
  std::string* str = &strRef;
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags,
                   InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextMultiline(const char* label,
                               std::string& strRef,
                               const ImVec2& size,
                               ImGuiInputTextFlags flags,
                               ImGuiInputTextCallback callback,
                               void* user_data) {
  std::string* str = &strRef;
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1,
                            size, flags, InputTextCallback, &cb_user_data);
}
