#pragma once

#include <string>

namespace xhfr {

struct DropEvent {
  enum DropEventType { File, Text } dropEventType;
  std::string data;
};

}  // namespace xhfr
