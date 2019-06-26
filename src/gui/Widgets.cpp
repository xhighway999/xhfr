#include "Widgets.hpp"

void ImGui::AutoPlot(const char *label,
                     float *newValue,
                     float *values,
                     int values_count,
                     const char *overlay_text,
                     float scale_min,
                     float scale_max,
                     ImVec2 graph_size,
                     int stride) {
  
  ImGui::PushID(label);
  
  ImGuiID refreshTimeId = ImGui::GetID("refresh_time");
  ImGuiID valuesOffsetId = ImGui::GetID("values_offset");
  double refresh_time  = ImGui::GetStateStorage()->GetFloat(refreshTimeId, ImGui::GetTime());
  if (refresh_time == 0.0)
    refresh_time = ImGui::GetTime();
  
  int values_offset = ImGui::GetStateStorage()->GetInt(valuesOffsetId, 0);
  while(refresh_time < ImGui::GetTime()) {
    values[values_offset] = *newValue;
    values_offset         = (values_offset + 1) % values_count;
    refresh_time += 1.0f / 60.0f;
    
  }
  ImGui::PlotLines(label,
                   values,
                   values_count,
                   values_offset,
                   overlay_text,
                   scale_min,
                   scale_max,
                   graph_size,
                   stride);
  ImGui::SameLine();
  ImGui::Text("%f", values[values_offset - 1]);
  ImGui::GetStateStorage()->SetFloat(refreshTimeId, refresh_time);
  ImGui::GetStateStorage()->SetInt(valuesOffsetId, values_offset);
  ImGui::PopID();
  
}
