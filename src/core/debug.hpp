#pragma once

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#define XHFR_ERROR(...) \
  SPDLOG_LOGGER_CALL(xhfr::debug::logger, spdlog::level::err, __VA_ARGS__)
#define XHFR_WARN(...) \
  SPDLOG_LOGGER_CALL(xhfr::debug::logger, spdlog::level::warn, __VA_ARGS__)
#define XHFR_INFO(...) \
  SPDLOG_LOGGER_CALL(xhfr::debug::logger, spdlog::level::info, __VA_ARGS__)
#define XHFR_DEBUG(...) \
  SPDLOG_LOGGER_CALL(xhfr::debug::logger, spdlog::level::debug, __VA_ARGS__)

namespace xhfr {

class debug {
 public:
  void initLogging();
  debug();
  static spdlog::logger* logger;
};

}  // namespace xhfr
