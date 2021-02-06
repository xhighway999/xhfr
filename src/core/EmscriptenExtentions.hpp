#pragma once

#include <cmath>
#include <string>
#include "../fs/File.hpp"
#ifdef __EMSCRIPTEN__
namespace xhfr {
void emscripten_download_data(const char* ptr,
                              size_t l,
                              const char* downloadFileName,
                              std::string mimeType = "text/plain");
void emscripten_download_file(std::string path,
                              std::string displayName,
                              std::string mimeType);
}  // namespace xhfr
#else
namespace xhfr {
void emscripten_download_data(const char* ptr,
                              size_t l,
                              const char* downloadFileName,
                              std::string mimeType = "text/plain");
void emscripten_download_file(std::string path,
                              std::string displayName,
                              std::string mimeType);
}  // namespace xhfr
#endif
