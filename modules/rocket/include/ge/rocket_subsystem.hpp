#ifndef GE_ROCKET_SUBSYSTEM_HPP
#define GE_ROCKET_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"

#include "ge/rocket_render_interface.hpp"
#include "ge/rocket_system_interface.hpp"

#include "Rocket/Core.h"

namespace ge
{
/// A subsystem for running Rocket
struct rocket_subsystem : subsystem {
	/// Empty config object, no need for any config yet
	struct config {
	};

	/// Initialize function for subsystems
	bool initialize(config c);

	/// Update function for subsystems
	bool update(std::chrono::duration<float> delta) override;

	/// Shutdown function for subsystems
	bool shutdown() override;

	/// The  rocket context--the subsystem owns it.
	Rocket::Core::Context* m_context;
};

}  // ge

#endif  // GE_ROCKET_SUBSYSTEM_HPP
