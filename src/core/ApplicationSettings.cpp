#include "ApplicationSettings.hpp"

namespace xhfr {

ApplicationSettings::ApplicationSettings() {}

void ApplicationSettings::save() {
  std::string saveLocation = "./applicationsettings.json";
#ifdef __EMSCRIPTEN__
  saveLocation = "/persistent/applicationsettings.json";
#endif
  std::string s = json.dump();
  xhfr::File f;
  XHFR_DEBUG("Updating application settings");
  if (f.open(saveLocation, true)) {
    f.write(s);
    f.close();
  } else {
    XHFR_ERROR("Could not open ApplicationSettings file for writing");
  };
}

void ApplicationSettings::load() {
  std::string saveLocation = "./applicationsettings.json";
#ifdef __EMSCRIPTEN__
  saveLocation = "/persistent/applicationsettings.json";
#endif

  if (!xhfr::fs::exists(saveLocation)) {
    XHFR_DEBUG("Could not find existing ApplicationSettings");
    return;
  }
  xhfr::File f;
  if (f.open(saveLocation, false)) {
    std::string d = f.readAll();
    json = json.parse(d);
    f.close();
  }
}

}  // namespace xhfr
