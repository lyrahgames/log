#pragma once
#include <lyrahgames/log/severity.hpp>
#include <lyrahgames/log/utility.hpp>

namespace lyrahgames::log::console {

constexpr auto default_severity_string(severity_level s) noexcept -> czstring {
  switch (s) {
    case severity_level::debug:
      return "DEBUG:";
      break;
    case severity_level::info:
      return "INFO:";
      break;
    case severity_level::warning:
      return "WARNING:";
      break;
    case severity_level::error:
      return "ERROR:";
      break;
    case severity_level::fatal:
      return "FATAL:";
      break;
    case severity_level::stats:
      return "STATS:";
      break;
    default:
      return "UNKNOWN:";
  }
}

constexpr auto default_severity_style(severity_level s) noexcept -> text_style {
  switch (s) {
    case severity_level::debug:
      return emphasis::bold | fg(color::white_smoke);
      break;
    case severity_level::info:
      return emphasis::bold | fg(color::green);
      break;
    case severity_level::warning:
      return emphasis::bold | fg(color::orange);
      break;
    case severity_level::error:
      return emphasis::bold | fg(color::red);
      break;
    case severity_level::fatal:
      return emphasis::bold | fg(color::dark_red);
      break;
    case severity_level::stats:
      return emphasis::bold | fg(color::deep_sky_blue);
      break;
    default:
      return {};
  }
}

template <severity_level severity>
inline auto default_severity_format() -> string {
  return fmt::format(default_severity_style(severity), "{0:<{1}}",
                     default_severity_string(severity), 10);
}

inline auto default_source_location_format(source_location location) -> string {
  return fmt::format(
      "{} {}:",
      fmt::format(emphasis::bold, "{}:{}:{}: ",  //
                  filesystem::relative(location.file_name()).c_str(),
                  location.line(), location.column()),
      location.function_name());
}

inline auto default_date_format(auto time_stamp) -> string {
  const auto date =
      chrono::year_month_day{chrono::floor<chrono::days>(time_stamp)};
  return fmt::format("{:>4}-{:0>2}-{:0>2}",  //
                     static_cast<int>(date.year()),
                     static_cast<unsigned>(date.month()),
                     static_cast<unsigned>(date.day()));
}

inline auto default_time_format(auto time_stamp) -> string {
  const auto time =
      chrono::hh_mm_ss{time_stamp - chrono::floor<chrono::days>(time_stamp)};
  return fmt::format("{:0>2}:{:0>2}:{:0>2}",  //
                     time.hours().count(),    //
                     time.minutes().count(),  //
                     time.seconds().count());
}

inline auto default_thread_id_format(thread::id id) -> string {
  return fmt::format("{}", id);
}

inline void default_log(auto&& message) {
  using message_type = decay_t<decltype(message)>;

  // if constexpr (exists<"severity">(message)) {
  //   constexpr auto severity = type<"severity">(message)::value;
  //   print("{}", default_severity_format<severity>());
  // }

  // if constexpr (exists<"time">(message)) {
  //   const auto time = value<"time">(forward<decltype(message)>(message));
  //   print("{} {}", default_date_format(time), default_time_format(time));
  // }

  print("{}\n", value<0>(message));
}

inline void log(auto&& package) {
  using package_type = decay_t<decltype(package)>;

  if constexpr (package_type::template contains<"severity">) {
    using severity = decay_t<decltype(value<"severity">(package))>;
    print("{}", default_severity_format<severity::value>());
  }

  if constexpr (package_type::template contains<"source location">)
    print("{}\n", default_source_location_format(value<"source location">(
                      forward<decltype(package)>(package))));

  print("  {}", value<"message">(forward<decltype(package)>(package)));

  if constexpr (package_type::template contains<"time">)
    print(" [{} {}]", default_date_format(value<"time">(package)),
          default_time_format(
              value<"time">(forward<decltype(package)>(package))));

  using other_attributes = typename package_type::names::try_remove_value<
      "severity"_sz>::try_remove_value<"source location"_sz>::
      try_remove_value<"message"_sz>::try_remove_value<"time"_sz>;
  other_attributes::for_each([&]<auto name> {
    // if constexpr (meta::equal<string,
    //                           decltype(fmt::format(value<name>(
    //                               forward<decltype(package)>(package))))>) {
    print(" [{} = {}]", name.data(),
          value<name>(forward<decltype(package)>(package)));
    // } else {
    //   print(" [{} = ?]", name.data());
    // }
  });

  cout << '\n' << endl;
}

}  // namespace lyrahgames::log::console

namespace lyrahgames::log {

struct console_log {
  //
  static auto to_string(auto&& x) -> czstring { return "{?}"; }

  static auto to_string(auto&& x) -> string  //
    requires requires(ostream& os) { os << x; }
  {
    return (stringstream{} << x).str();
  }

  template <severity_level severity>
  static auto to_string(severity_tag::tag<severity>) -> string {
    return fmt::format(console::default_severity_style(severity), "{0:<{1}}",
                       console::default_severity_string(severity), 10);
  }

  static auto to_string(source_location location) -> string {
    return fmt::format(
        emphasis::faint, "{} {}:",
        fmt::format("{}:{}:{}:",  //
                    filesystem::relative(location.file_name()).c_str(),
                    location.line(), location.column()),
        fmt::format(emphasis::italic, "{}", location.function_name()));
  }

  static auto to_string(chrono::time_point<chrono::system_clock> time_stamp)
      -> string {
    const auto date =
        chrono::year_month_day{chrono::floor<chrono::days>(time_stamp)};
    const auto time =
        chrono::hh_mm_ss{time_stamp - chrono::floor<chrono::days>(time_stamp)};
    return fmt::format("{} {}",
                       fmt::format("{:>4}-{:0>2}-{:0>2}",  //
                                   static_cast<int>(date.year()),
                                   static_cast<unsigned>(date.month()),
                                   static_cast<unsigned>(date.day())),
                       fmt::format("{:0>2}:{:0>2}:{:0>2}",  //
                                   time.hours().count(),    //
                                   time.minutes().count(),  //
                                   time.seconds().count()));
  }

  template <static_zstring name>
  static auto to_string(auto&& x) -> string {
    return to_string(forward<decltype(x)>(x));
  }

  // template <static_zstring name>
  // static auto to_string(auto&& x) -> string  //
  //     requires(name == "note"_sz) {
  //   return fmt::format(emphasis::faint | emphasis::italic, "{}",
  //                 forward<decltype(x)>(x));
  // }

  static void log(auto&& package) {
    using package_type = decay_t<decltype(package)>;
    using attributes = typename package_type::names;
    attributes::for_each([&]<auto name> {
      print("{} = {}\n", name.data(),
            to_string<name>(value<name>(forward<decltype(package)>(package))));
    });
    cout << endl;
  }
};

struct clog : console_log {
  static void log(auto&& package) {
    using package_type = decay_t<decltype(package)>;

    if constexpr (package_type::template contains<"severity">)
      print("{}", to_string(value<"severity">(package)));

    if constexpr (package_type::template contains<"time">)
      print(emphasis::faint, "[{}]\n", to_string(value<"time">(package)));

    if constexpr (package_type::template contains<"source location">)
      print("│         {}\n│\n", to_string(value<"source location">(package)));

    if constexpr (package_type::template contains<"message">)
      print("└───────── {}\n", to_string(value<"message">(package)));

    // using attributes = typename package_type::names;
    // attributes::for_each([&]<auto name> {
    //   print("{} = {}\n", name.data(),
    //         to_string<name>(value<name>(forward<decltype(package)>(package))));
    // });
    cout << endl;
  }
};

}  // namespace lyrahgames::log
