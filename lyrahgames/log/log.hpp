#pragma once
#include <lyrahgames/log/version.hpp>
//
#include <lyrahgames/log/debug_log.hpp>
#include <lyrahgames/log/release_log.hpp>
//
#include <lyrahgames/log/core.hpp>

namespace lyrahgames::log {

#ifdef NDEBUG
using log = log::release_log;
#else
using log = log::debug_log;
#endif

}  // namespace lyrahgames::log
