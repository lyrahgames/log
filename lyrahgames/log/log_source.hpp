#pragma once
#include <lyrahgames/log/core.hpp>
#include <lyrahgames/log/severity.hpp>
#include <lyrahgames/log/utility.hpp>

namespace lyrahgames::log {

struct log_source {
  static void log(auto&& message,
                  auto severity,
                  source_location location = source_location::current()) {
    core::log(auto_named_tuple<"message", "severity", "source location", "time",
                               "thread", "note">(
        message, severity, location, chrono::system_clock::now(),
        this_thread::get_id(), "This is a note."));
  }

  static void debug(auto&& message,
                    source_location location = source_location::current()) {
    log(forward<decltype(message)>(message), severity_tag::debug, location);
  }

  static void info(auto&& message,
                   source_location location = source_location::current()) {
    log(forward<decltype(message)>(message), severity_tag::info, location);
  }

  static void warning(auto&& message,
                      source_location location = source_location::current()) {
    log(forward<decltype(message)>(message), severity_tag::warning, location);
  }

  static void error(auto&& message,
                    source_location location = source_location::current()) {
    log(forward<decltype(message)>(message), severity_tag::error, location);
  }

  static void fatal(auto&& message,
                    source_location location = source_location::current()) {
    log(forward<decltype(message)>(message), severity_tag::fatal, location);
  }
};

}  // namespace lyrahgames::log
