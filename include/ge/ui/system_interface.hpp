#ifndef GE_SYSTEM_INTERFACE_HPP
#define GE_SYSTEM_INTERFACE_HPP

#pragma once

#include "ge/runtime.hpp"

#include <Rocket/Core/SystemInterface.h>

namespace ge
{
namespace ui
{
class system_interface : public Rocket::Core::SystemInterface
{
public:
	system_interface(runtime& arg_app) : m_runtime{arg_app} {};

private:
	virtual float GetElapsedTime() override { return m_runtime.get_elapsed_time().count(); }
	runtime& m_runtime;
};
}
}

#endif  // GE_SYSTEM_INTERFACE_HPP
