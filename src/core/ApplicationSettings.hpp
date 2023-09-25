#pragma once

#include "../fs/File.hpp"
#include "debug.hpp"
#include "nlohmann/json.hpp"
namespace xhfr {

class ApplicationSettings {
 public:
  ApplicationSettings();

  template <typename T>
  void setValue(std::string s, const T& val) {
    std::string delimiter = "/";

    size_t pos = 0;
    std::string token;
    auto ptr = nlohmann::json_pointer<nlohmann::json>(s.c_str());
    json[ptr] = val;
    /*auto& it = json["x"];
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        it = it[token];
        s.erase(0, pos + delimiter.length());
    }
    it[s] = val;*/
    save();
  }

  template <typename T>
  T value(std::string s, T defaultValue = T()) {
    if (!loaded) {
      load();
      loaded = true;
    }

    auto ptr = nlohmann::json_pointer<nlohmann::json>(s.c_str());
    if (json[ptr].is_null()) {
      json[ptr] = defaultValue;
      save();

      return defaultValue;
    }
    return json[ptr];
  }

 private:
  void save();
  void load();
  bool loaded = false;
  nlohmann::json json;
};

}  // namespace xhfr
