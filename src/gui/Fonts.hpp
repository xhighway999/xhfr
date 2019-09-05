#ifndef FONTS_HPP
#define FONTS_HPP

#include "../fs/File.hpp"
#include "imgui.h"

#ifdef XHFR_FREETYPE
#include "imgui_freetype.h"
#endif

namespace xhfr {

class FontManager {
  FontManager() = default;

 public:
  FontManager(FontManager const&) = delete;
  void operator=(FontManager const&) = delete;
  static FontManager& getInstance();
  void addDefaultFont();
  ImFont* addFont(const char* path, float size, ImFontConfig* cfg = nullptr);
  void build();

 private:
};

};  // namespace xhfr

#endif  // FONTS_HPP
