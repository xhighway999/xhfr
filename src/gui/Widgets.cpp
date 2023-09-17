#include "Widgets.hpp"
#include "../core/compat.hpp"
#include "imgui_internal.h"

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

bool ImGui::Link(const char* linkText, const char* link, ImColor color) {
  auto pos = ImGui::GetCursorScreenPos();
  // https://github.com/xhighway999/luapad

  if (link == nullptr) {
    link = linkText;
  }

  auto size = ImGui::CalcTextSize(linkText);
  ImGui::TextColored(color, linkText);
  auto draw_list = ImGui::GetWindowDrawList();
  pos.y += ImGui::GetTextLineHeight();
  pos.y += 3;
  draw_list->AddLine(pos, ImVec2(pos.x + size.x, pos.y), color, 1);
  if (ImGui::IsItemClicked()) {
    xhfr::openURL(link);
    return true;
  }
  return false;
}

bool ImageButtonWithText(ImTextureID texId,
                         std::string label,
                         const ImVec2& imageSize,
                         const ImVec2& uv0,
                         const ImVec2& uv1,
                         int frame_padding,
                         const ImVec4& bg_col,
                         const ImVec4& tint_col) {
  return ImageButtonWithText(texId, label.c_str(), imageSize, uv0, uv1,
                             frame_padding, bg_col, tint_col);
}

bool ImGui::ImageButtonWithText(ImTextureID texId,
                                const char* label,
                                const ImVec2& imageSize,
                                const ImVec2& uv0,
                                const ImVec2& uv1,
                                int frame_padding,
                                const ImVec4& bg_col,
                                const ImVec4& tint_col) {
  ImGuiWindow* window = GetCurrentWindow();
  if (window->SkipItems)
    return false;

  ImVec2 size = imageSize;
  if (size.x <= 0 && size.y <= 0) {
    size.x = size.y = ImGui::GetTextLineHeightWithSpacing();
  } else {
    if (size.x <= 0)
      size.x = size.y;
    else if (size.y <= 0)
      size.y = size.x;
    size *= window->FontWindowScale * ImGui::GetIO().FontGlobalScale;
  }

  ImGuiContext& g = *GImGui;
  const ImGuiStyle& style = g.Style;

  const ImGuiID id = window->GetID(label);
  const ImVec2 textSize = ImGui::CalcTextSize(label, NULL, true);
  const bool hasText = textSize.x > 0;

  const float innerSpacing =
      hasText ? ((frame_padding >= 0) ? (float)frame_padding
                                      : (style.ItemInnerSpacing.x))
              : 0.f;
  const ImVec2 padding =
      (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding)
                           : style.FramePadding;
  const ImVec2 totalSizeWithoutPadding(
      size.x + innerSpacing + textSize.x,
      size.y > textSize.y ? size.y : textSize.y);
  const ImRect bb(window->DC.CursorPos,
                  window->DC.CursorPos + totalSizeWithoutPadding + padding * 2);
  ImVec2 start(0, 0);
  start = window->DC.CursorPos + padding;
  if (size.y < textSize.y)
    start.y += (textSize.y - size.y) * .5f;
  const ImRect image_bb(start, start + size);
  start = window->DC.CursorPos + padding;
  start.x += size.x + innerSpacing;
  if (size.y > textSize.y)
    start.y += (size.y - textSize.y) * .5f;
  ItemSize(bb);
  if (!ItemAdd(bb, id))
    return false;

  bool hovered = false, held = false;
  bool pressed = ButtonBehavior(bb, id, &hovered, &held);

  // Render
  const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive
                                : hovered         ? ImGuiCol_ButtonHovered
                                                  : ImGuiCol_Button);
  RenderFrame(
      bb.Min, bb.Max, col, true,
      ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
  if (bg_col.w > 0.0f)
    window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max,
                                    GetColorU32(bg_col));

  window->DrawList->AddImage(texId, image_bb.Min, image_bb.Max, uv0, uv1,
                             GetColorU32(tint_col));

  if (textSize.x > 0)
    ImGui::RenderText(start, label);
  return pressed;
}
