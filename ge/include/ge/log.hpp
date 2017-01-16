#ifndef GE_LOG_HPP
#define GE_LOG_HPP

#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace ge
{
extern std::shared_ptr<spdlog::logger> logger;
}

#endif  // GE_LOG_HPP
