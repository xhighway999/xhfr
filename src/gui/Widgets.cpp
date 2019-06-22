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
  char cat[512];
  strcpy(cat, label);
  strcat(cat, "refresh_time");
  float &refresh_time =
      *ImGui::GetStateStorage()->GetFloatRef(ImGui::GetID(cat), 0);
  strcpy(cat, label);
  strcat(cat, "values_offset");
  int &values_offset =
      *ImGui::GetStateStorage()->GetIntRef(ImGui::GetID(cat), 0);
  if(refresh_time == 0.0)
    refresh_time = ImGui::GetTime();
  while(refresh_time < ImGui::GetTime()) {
    static float phase    = 0.0f;
    values[values_offset] = *newValue;
    values_offset         = (values_offset + 1) % values_count;
    phase += 0.10f * values_offset;
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
}
