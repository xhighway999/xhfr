#include "Canvas.hpp"

#define NANOVG_RT_IMPLEMENTATION
#define NANORT_IMPLEMENTATION
//#include "nanort.h"
//#include "nanovg.h"

#include "Fonts.hpp"
#include "imgui.h"
#include "nanovg_rt.h"
#include "stb_image_resize.h"

namespace xhfr {

Canvas::Canvas() {}

Canvas::~Canvas() {
  nvgDeleteRT(vg);
}

void Canvas::create(size_t w, size_t h, bool debug) {
  int flags = NVG_ANTIALIAS;
  if (debug) {
    flags |= NVG_DEBUG;
  }
  vg = nvgCreateRT(flags, w * scaleFactor, h * scaleFactor);
  begin();
  dispSize.x = w;
  dispSize.y = h;
  size.x = w * scaleFactor;
  size.y = h * scaleFactor;
  FontManager& fm = FontManager::getInstance();
  auto fontInfo = fm.getInstalledFonts()[0];
  xhfr::File f(fontInfo.second);
  auto size = f.size();
  fontSize = 16 * scaleFactor;
  unsigned char* data = (unsigned char*)malloc(size);
  f.read(data, size);
  int handle = nvgCreateFontMem(vg, "default", data, size, 1);
  if (handle == -1) {
    XHFR_ERROR("Failed loading font {}", fontInfo.second);
  }
}

void Canvas::save(std::string path) {}

void Canvas::clearBackground(Canvas::Color c) {
  nvgClearBackgroundRT(vg, c.r, c.g, c.b, c.a);
}

void Canvas::drawLine(Canvas::Color c,
                      Canvas::Vector a,
                      Canvas::Vector b,
                      float t) {
  nvgBeginPath(vg);
  a *= scaleFactor;
  b *= scaleFactor;
  nvgMoveTo(vg, a.x, a.y);
  nvgLineTo(vg, b.x, b.y);
  nvgStrokeColor(vg, nvgRGBAf(c.r, c.g, c.b, c.a));
  nvgStrokeWidth(vg, t * scaleFactor);
  nvgStroke(vg);
}

void Canvas::AddLine(const ImVec2& p1,
                     const ImVec2& p2,
                     ImU32 col,
                     float thickness) {
  drawLine(col, p1, p2, thickness);
}

void Canvas::AddRect(const ImVec2& p_min,
                     const ImVec2& p_max,
                     ImU32 col,
                     float rounding,
                     ImDrawFlags rounding_corners,
                     float thickness) {
  nvgBeginPath(vg);
  Vector a = p_min, b = p_max;
  a *= scaleFactor;
  b *= scaleFactor;
  // nvg uses size not coordinates
  Vector size = b - a;
  nvgRoundedRect(vg, a.x, a.y, size.x, size.y, rounding);
  Color c(col);
  nvgStrokeColor(vg, nvgRGBAf(c.r, c.g, c.b, c.a));
  nvgStrokeWidth(vg, thickness * scaleFactor);
  nvgStroke(vg);
}

void Canvas::AddRectFilled(const ImVec2& p_min,
                           const ImVec2& p_max,
                           ImU32 col,
                           float rounding,
                           ImDrawFlags rounding_corners) {
  nvgBeginPath(vg);
  Vector a = p_min, b = p_max;
  a *= scaleFactor;
  b *= scaleFactor;
  Vector size = b - a;
  nvgRoundedRect(vg, a.x, a.y, size.x, size.y, rounding);
  Color c(col);
  nvgFillColor(vg, nvgRGBAf(c.r, c.g, c.b, c.a));
  nvgFill(vg);
}

void Canvas::AddText(const ImVec2& pos,
                     ImU32 col,
                     const char* text_begin,
                     const char* text_end) {
  nvgFontSize(vg, fontSize);
  nvgFontFace(vg, "default");
  nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
  Color c(col);
  Vector a = pos;
  a *= scaleFactor;
  nvgFillColor(vg, nvgRGBAf(c.r, c.g, c.b, c.a));
  nvgText(vg, a.x, a.y, text_begin, text_end);
}

void Canvas::setScaleFactor(float value) {
  scaleFactor = value;
}

unsigned char* Canvas::readPixels() {
  return nvgReadPixelsRT(vg);
}

std::vector<unsigned char> Canvas::getResizedImageData() {
  unsigned char* rgba = nvgReadPixelsRT(vg);
  std::vector<unsigned char> image;
  image.resize(dispSize.x * dispSize.y * 4);
  stbir_resize_uint8(rgba, size.x, size.y, size.x * 4, image.data(), dispSize.x,
                     dispSize.y, dispSize.x * 4, 4);

  return image;
}

Canvas::Vector Canvas::getSize() const {
  return dispSize;
}

Canvas::Vector Canvas::getRenderSize() const {
  return size;
}

void Canvas::begin() {
  nvgBeginFrame(vg, size.x, size.y, 1);
  clearBackground(Color(255.f, 0.f, 255.f, 0.f));
}

void Canvas::end() {
  nvgEndFrame(vg);
}

void Canvas::renderImage(Image& i) {
  // no alllocation is made in nevgTeadPixelsRT
  unsigned char* rgba = nvgReadPixelsRT(vg);
  i.loadImageFromRaw(rgba, size.x, size.y, 4);
}

}  // namespace xhfr
