#include "Fonts.hpp"

namespace xhfr {

FontManager& FontManager::getInstance() {
  static FontManager instance;
  return instance;
}

void FontManager::addDefaultFont() {
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
}

ImFont* FontManager::addFont(const char* path, float size, ImFontConfig* cfg) {
  ImGuiIO& io = ImGui::GetIO();
  // io.Fonts->AddFontDefault();
  xhfr::File file(path);
  ImFontConfig font_cfg = cfg ? *cfg : ImFontConfig();
  font_cfg.FontDataOwnedByAtlas = false;
  memcpy(font_cfg.Name, path, strlen(path) < 40 ? strlen(path) : 40);
  font_cfg.Name[39] = '\0';
  return io.Fonts->AddFontFromMemoryTTF((void*)file.readAll().data(),
                                        file.size(), size, &font_cfg);
}

void FontManager::build() {
  ImGuiIO& io = ImGui::GetIO();
  if (io.Fonts->Fonts.size() == 0) {
    addDefaultFont();
  }

#ifdef XHFR_FREETYPE
  unsigned int flags = ImGuiFreeType::NoHinting;
  ImGuiFreeType::BuildFontAtlas(io.Fonts, flags);
#else
  io.Fonts->Build();
#endif
}

}  // namespace xhfr
