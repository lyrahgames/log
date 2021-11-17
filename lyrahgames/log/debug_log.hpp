#pragma once
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
//
#ifdef __clang__
#include <experimental/source_location>
namespace lyrahgames::log {
using source_location = std::experimental::source_location;
}
#else
#include <source_location>
namespace lyrahgames::log {
using source_location = std::source_location;
}
#endif
//

namespace lyrahgames::log {

using namespace std;
using namespace fmt;
using namespace fmt::literals;

class debug_log {
 public:
  void info(auto&& x, source_location location = source_location::current());
  void warning(auto&& x, source_location location = source_location::current());
  void error(auto&& x, source_location location = source_location::current());

  bool quiet = false;

 private:
  static constexpr size_t indent = 10;

  auto to_string(source_location location);
  auto prefix(auto&& style, auto&& str);
  auto indent_string();
  auto log(auto& stream,
           auto&& pre,
           auto&& x,
           source_location location = source_location::current());
};

inline auto debug_log::to_string(source_location location) {
  return format(
      "{} {}:",
      format(emphasis::bold, "{}:{}:{}: ",  //
             location.file_name(), location.line(), location.column()),
      location.function_name());
}

inline auto debug_log::prefix(auto&& style, auto&& str) {
  return format(forward<decltype(style)>(style), "{0:<{1}}",
                forward<decltype(str)>(str), indent);
}

inline auto debug_log::indent_string() {
  return format("{0:<{1}}", "", indent);
}

inline auto debug_log::log(auto& stream,
                           auto&& pre,
                           auto&& x,
                           source_location location) {
  print(stream, "{}{}\n{}{}\n\n", forward<decltype(pre)>(pre),
        to_string(location), indent_string(), forward<decltype(x)>(x));
}

inline void debug_log::info(auto&& x, source_location location) {
  if (quiet)
    return;
  log(stdout, prefix(fg(color::green), "INFO:"), forward<decltype(x)>(x),
      location);
}

inline void debug_log::warning(auto&& x, source_location location) {
  if (quiet)
    return;
  log(stderr, prefix(fg(color::orange), "WARNING:"), forward<decltype(x)>(x),
      location);
}

inline void debug_log::error(auto&& x, source_location location) {
  log(stderr, prefix(fg(color::red), "ERROR:"), forward<decltype(x)>(x),
      location);
}

}  // namespace lyrahgames::log
