#include "ExtendedImgui.hpp"

/*
bool ImGui::ImageButton(const xcge::Texture &texture, ImVec2 size) {


    //If the size is 0 scale the button to normal size
    if (size.x == 0 && size.y == 0) {
        size.x = size.y = GetTextLineHeight();
    }
    //We need to flip the Image in the Y axis because imgur shows them
    //flipped for some Reason
    return ImageButton(reinterpret_cast<GLuint*>(texture.id()),size,
                       ImVec2(0,1),ImVec2(1,0));
}
*/

static int InputTextCallback(ImGuiInputTextCallbackData *data) {
  ImGui::InputTextCallback_UserData *user_data =
      (ImGui::InputTextCallback_UserData *)data->UserData;
  if(data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    // Resize string callback
    std::string *str = user_data->Str;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char *)str->c_str();
  } else if(user_data->ChainCallback) {
    // Forward to user callback, if any
    data->UserData = user_data->ChainCallbackUserData;
    return user_data->ChainCallback(data);
  }
  return 0;
}

bool ImGui::InputText(const char *label,
                      std::string &strRef,
                      ImGuiInputTextFlags flags,
                      ImGuiInputTextCallback callback,
                      void *user_data) {
  std::string *str = &strRef;
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str                   = str;
  cb_user_data.ChainCallback         = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return InputText(label,
                   (char *)str->c_str(),
                   str->capacity() + 1,
                   flags,
                   InputTextCallback,
                   &cb_user_data);
}

bool ImGui::InputTextMultiline(const char *label,
                               std::string &strRef,
                               const ImVec2 &size,
                               ImGuiInputTextFlags flags,
                               ImGuiInputTextCallback callback,
                               void *user_data) {
  std::string *str = &strRef;
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str                   = str;
  cb_user_data.ChainCallback         = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return InputTextMultiline(label,
                            (char *)str->c_str(),
                            str->capacity() + 1,
                            size,
                            flags,
                            InputTextCallback,
                            &cb_user_data);
}
/*
void ImGui::Image(const xcge::Texture &texture, ImVec2 size) {
    ImGui::Image(reinterpret_cast<GLuint*>(texture.id()),size,
            ImVec2(0,1),ImVec2(1,0));
}
*/
