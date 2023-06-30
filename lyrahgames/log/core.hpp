#pragma once
#include <iostream>
#include <mutex>
//
#include <lyrahgames/log/console.hpp>
#include <lyrahgames/log/utility.hpp>

namespace lyrahgames::log {

struct core {
  inline static std::mutex mutex{};
  static void log(auto&& message) {
    scoped_lock lock{mutex};
    // console_log::log(message);
    clog::log(message);
    // console::log(forward<decltype(message)>(message));
  }
};

}  // namespace lyrahgames::log
