#pragma once
#include <type_traits>

namespace lyrahgames::log {

enum class severity_level : int { debug, info, warning, error, fatal, stats };

namespace severity_tag {

template <severity_level level>
using tag = std::integral_constant<severity_level, level>;

inline constexpr tag<severity_level::debug> debug{};
inline constexpr tag<severity_level::info> info{};
inline constexpr tag<severity_level::warning> warning{};
inline constexpr tag<severity_level::error> error{};
inline constexpr tag<severity_level::fatal> fatal{};
inline constexpr tag<severity_level::stats> stats{};

}  // namespace severity_tag

}  // namespace lyrahgames::log
