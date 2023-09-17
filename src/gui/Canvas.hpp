#pragma once

/*this is a tiny canvas implementation inspired from
 * https://github.com/lexus2k/canvas as it is incredibly lightweight (no
 * dependencies) and one of the few libraries that does not come with
 * dependencies */

#include <string>
#include "nanovg.h"
#include "nanovg_rt.h"

#include "Image.hpp"
#include "imgui.h"

namespace xhfr {

class Canvas {
 public:
  struct Color {
    float r, g, b, a = 255;
    Color() = default;
    Color(float r, float g, float b, float a = 255) {
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    }
    Color(ImU32 c) {
      ImColor col(c);
      ImVec4 conv = col;
      r = conv.x;
      g = conv.y;
      b = conv.z;
      a = conv.w;
    }
  };

  struct Vector {
    Vector() = default;
    Vector(ImVec2 v) {
      x = v.x;
      y = v.y;
    }
    void operator*=(float f) {
      x *= f;
      y *= f;
    }
    Vector operator-(Vector rhs) {
      Vector c;
      c.x = this->x - rhs.x;
      c.y = this->y - rhs.y;
      return c;
    }
    float x, y;
  };

  Canvas();
  ~Canvas();
  void create(size_t w, size_t h, bool debug = false);
  void save(std::string path);
  void clearBackground(Color c);
  void drawLine(Color c, Vector a, Vector b, float t = 1);
  Vector getSize() const;
  Vector getRenderSize() const;
  void begin();
  void end();
  void renderImage(Image& i);
  void setScaleFactor(float value);
  unsigned char* readPixels();
  std::vector<unsigned char> getResizedImageData();
  // everyyhing below is the IMGUI api, provided for campability
  void AddLine(const ImVec2& p1,
               const ImVec2& p2,
               ImU32 col,
               float thickness = 1.0f);
  void AddRect(
      const ImVec2& p_min,
      const ImVec2& p_max,
      ImU32 col,
      float rounding = 0.0f,
      ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll,
      float thickness = 1.0f);  // a: upper-left, b: lower-right (== upper-left
                                // + size), rounding_corners_flags: 4 bits
                                // corresponding to which corner to round
  void AddRectFilled(
      const ImVec2& p_min,
      const ImVec2& p_max,
      ImU32 col,
      float rounding = 0.0f,
      ImDrawFlags rounding_corners =
          ImDrawFlags_RoundCornersAll);  // a: upper-left, b: lower-right (==
                                   // upper-left + size)
  void AddRectFilledMultiColor(const ImVec2& p_min,
                               const ImVec2& p_max,
                               ImU32 col_upr_left,
                               ImU32 col_upr_right,
                               ImU32 col_bot_right,
                               ImU32 col_bot_left);
  void AddQuad(const ImVec2& p1,
               const ImVec2& p2,
               const ImVec2& p3,
               const ImVec2& p4,
               ImU32 col,
               float thickness = 1.0f);
  void AddQuadFilled(const ImVec2& p1,
                     const ImVec2& p2,
                     const ImVec2& p3,
                     const ImVec2& p4,
                     ImU32 col);
  void AddTriangle(const ImVec2& p1,
                   const ImVec2& p2,
                   const ImVec2& p3,
                   ImU32 col,
                   float thickness = 1.0f);
  void AddTriangleFilled(const ImVec2& p1,
                         const ImVec2& p2,
                         const ImVec2& p3,
                         ImU32 col);
  void AddCircle(const ImVec2& center,
                 float radius,
                 ImU32 col,
                 int num_segments = 12,
                 float thickness = 1.0f);
  void AddCircleFilled(const ImVec2& center,
                       float radius,
                       ImU32 col,
                       int num_segments = 12);
  void AddNgon(const ImVec2& center,
               float radius,
               ImU32 col,
               int num_segments,
               float thickness = 1.0f);
  void AddNgonFilled(const ImVec2& center,
                     float radius,
                     ImU32 col,
                     int num_segments);
  void AddText(const ImVec2& pos,
               ImU32 col,
               const char* text_begin,
               const char* text_end = NULL);
  void AddText(const ImFont* font,
               float font_size,
               const ImVec2& pos,
               ImU32 col,
               const char* text_begin,
               const char* text_end = NULL,
               float wrap_width = 0.0f,
               const ImVec4* cpu_fine_clip_rect = NULL);
  void AddPolyline(const ImVec2* points,
                   int num_points,
                   ImU32 col,
                   bool closed,
                   float thickness);
  void AddConvexPolyFilled(const ImVec2* points,
                           int num_points,
                           ImU32 col);  // Note: Anti-aliased filling requires
                                        // points to be in clockwise order.
  void AddBezierCurve(const ImVec2& p1,
                      const ImVec2& p2,
                      const ImVec2& p3,
                      const ImVec2& p4,
                      ImU32 col,
                      float thickness,
                      int num_segments = 0);

 private:
  float scaleFactor = 1;
  float fontSize = 16;
  NVGcontext* vg = nullptr;
  Vector size, dispSize;
};

}  // namespace xhfr
