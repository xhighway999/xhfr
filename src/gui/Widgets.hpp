#pragma once

#include "imgui.h"

#include <stdio.h>

namespace ImGui {
void AutoPlot(const char *label,
              float *newValue,
              float *values,
              int values_count,
              const char *overlay_text = NULL,
              float scale_min          = FLT_MAX,
              float scale_max          = FLT_MAX,
              ImVec2 graph_size        = ImVec2(0, 0),
              int stride               = sizeof(float));
}
