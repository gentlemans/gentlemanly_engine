#ifndef GE_SYSTEM_INTERFACE_HPP
#define GE_SYSTEM_INTERFACE_HPP

#pragma once

#include "ge/runtime.hpp"

#include <Rocket/Core/SystemInterface.h>

namespace ge
{
namespace ui
{
/// The Rocket SystemInterface for the engine. This gives rocket an interface for logging and time.
class system_interface : public Rocket::Core::SystemInterface
{
public:
	/// Constructor
	/// \param arg_app The runtime object to poll the time from.
	system_interface(runtime& arg_app) : m_runtime{arg_app} {};

private:
	virtual float GetElapsedTime() override { return m_runtime.get_elapsed_time().count(); }
	runtime& m_runtime;
};
}
}

#endif  // GE_SYSTEM_INTERFACE_HPP
