#include <cstring>
#include <iostream>
#include <string_view>
//
#include <lyrahgames/log/log.hpp>
#include <lyrahgames/log/log_source.hpp>

using namespace std;
using namespace lyrahgames;

using czstring = const char*;

auto next_white_space(czstring str) -> czstring {
  while (*str && *str != ' ') ++str;
  return str;
}

auto next_non_white_space(czstring str) -> czstring {
  while (*str == ' ') ++str;
  return str;
}

auto typesetted_string(const string& text) -> string {
  size_t width = 70;
  size_t offset = 10;
  string result(offset, ' ');

  size_t current_width = 0;
  czstring start = next_non_white_space(text.c_str());
  while (*start) {
    auto next = next_white_space(start);
    auto w = next - start;

    if (current_width + w > width) {
      result += '\n';
      result += string(offset, ' ');
      current_width = w;
    } else {
      result += ' ';
      current_width += w;
    }

    result += string_view{start, next};
    start = next_non_white_space(next);
  }

  return result;
}

// template <typename value_type, severity_level s>
// struct log_message {
//   static constexpr severity_level severity = s;
//   value_type value;
//   source_location location;
//   time_point time;
//   thread_id thread;
// };
// // decide with concepts

// void log(auto&& x);
// void log<severity>(auto&& x);
// void log(auto&& x, source_location);
// void log<severity>(auto&& x, source_location);

// void time_log(auto&& x);
// // ...

// void thread_log(auto&& x);
// // ...

// void thread_time_log(auto&& x);
// // ...

int main() {
  // log::log log{};
  // // log.quiet = true;
  // log.info("This is an information for the user.");
  // log.warning("This is a warning.");
  // log.error("This is an error.");

  // string unformatted_message =
  //     "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do "
  //     "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
  //     "ad "
  //     "minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
  //     "aliquip "
  //     "ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
  //     "voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
  //     "Excepteur "
  //     "sint occaecat cupidatat non proident, sunt in culpa qui officia "
  //     "deserunt mollit anim id est laborum.";
  // cout << unformatted_message << endl << endl;
  // cout << typesetted_string(unformatted_message) << endl;

  log::log_source::info("This is an information for the user.");
  log::log_source::warning("This is a warning.");
  log::log_source::error("This is an error.");
}
