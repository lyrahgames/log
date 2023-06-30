#pragma once
#include <filesystem>
#include <iomanip>
#include <iostream>
//
#include <chrono>
#include <thread>
//
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
// #include <fmt/std.h>
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
#include <lyrahgames/xstd/named_tuple.hpp>
#include <lyrahgames/xstd/static_zstring.hpp>

namespace lyrahgames::log {

using namespace std;

using namespace fmt;
using namespace fmt::literals;

using namespace xstd;

using fmt::v8::format;

}  // namespace lyrahgames::log
