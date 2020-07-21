#include "debug.hpp"

namespace xhfr {

spdlog::logger* xhfr::debug::logger = nullptr;

void debug::initLogging() {
  auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  sink->set_level(spdlog::level::trace);

  logger = new spdlog::logger("EDGE_Logger", {sink});
  logger->set_level(spdlog::level::trace);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%s:%#] %v");
  XHFR_INFO("Logger init done");
}

debug::debug() {}

}  // namespace xhfr
