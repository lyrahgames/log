#pragma once
#include <lyrahgames/log/debug_log.hpp>
#include <lyrahgames/log/release_log.hpp>
#include <lyrahgames/log/version.hpp>

namespace lyrahgames::log {

#ifdef NDEBUG
using log = log::release_log;
#else
using log = log::debug_log;
#endif

}  // namespace lyrahgames::log
