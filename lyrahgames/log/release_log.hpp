#pragma once
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

namespace lyrahgames::log {

using namespace std;
using namespace fmt;
using namespace fmt::literals;

class release_log {
 public:
  void info(auto&& x);
  void warning(auto&& x);
  void error(auto&& x);

  bool quiet = false;

 private:
  static constexpr size_t indent = 10;
  auto prefix(auto&& style, auto&& str);
  auto log(auto& stream, auto&& pre, auto&& x);
};

inline auto release_log::prefix(auto&& style, auto&& str) {
  return format(forward<decltype(style)>(style), "{0:<{1}}",
                forward<decltype(str)>(str), indent);
}

inline auto release_log::log(auto& stream, auto&& pre, auto&& x) {
  print(stream, "{}{}\n", forward<decltype(pre)>(pre), forward<decltype(x)>(x));
}

inline void release_log::info(auto&& x) {
  if (quiet) return;
  log(stdout, prefix(fg(color::green), "INFO:"), forward<decltype(x)>(x));
}

inline void release_log::warning(auto&& x) {
  if (quiet) return;
  log(stderr, prefix(fg(color::orange), "WARNING:"), forward<decltype(x)>(x));
}

inline void release_log::error(auto&& x) {
  log(stderr, prefix(fg(color::red), "ERROR:"), forward<decltype(x)>(x));
}

}  // namespace lyrahgames::log
