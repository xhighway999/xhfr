#pragma once

#include <cmath>
#include <string>

#ifdef __EMSCRIPTEN__
namespace xhfr {
void openURL(const char* url);
}  // namespace xhfr
#else
namespace xhfr {
void openURL(const char* url);
}  // namespace xhfr
#endif
