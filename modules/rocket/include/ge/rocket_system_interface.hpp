#ifndef GE_ROCKET_SYSTEM_INTERFACE_HPP
#define GE_ROCKET_SYSTEM_INTERFACE_HPP

#pragma once

#include "ge/runtime.hpp"

#include <Rocket/Core/SystemInterface.h>

namespace ge
{
/// The Rocket SystemInterface for the engine. This gives rocket an interface for logging and time.
class rocket_system_interface : public Rocket::Core::SystemInterface
{
public:
	/// Constructor
	/// \param arg_app The runtime object to poll the time from.
	rocket_system_interface(runtime& arg_app) : m_runtime{arg_app} {};

private:
	virtual float GetElapsedTime() override { return m_runtime.get_elapsed_time().count(); }
	virtual bool LogMessage(
		Rocket::Core::Log::Type type, const Rocket::Core::String& message) override
	{
		using Rocket::Core::Log;

		switch (type) {
		case Log::LT_ERROR: log->error(message.CString()); break;
		case Log::LT_ASSERT: log->critical(message.CString()); break;
		case Log::LT_WARNING: log->warn(message.CString()); break;
		case Log::LT_INFO: log->info(message.CString()); break;
		default: break;
		}
		return true;
	}
	runtime& m_runtime;
};
}

#endif  // GE_ROCKET_SYSTEM_INTERFACE_HPP
