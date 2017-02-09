#ifndef GE_ROCKET_INPUT_CONSUMER_HPP
#define GE_ROCKET_INPUT_CONSUMER_HPP

#pragma once

#include "ge/input_subsystem.hpp"
#include "ge/rocket_subsystem.hpp"

#include <Rocket/Core/Context.h>

namespace ge
{
/// This input consumer passes all input to Rocket
struct rocket_input_consumer : input_consumer<rocket_input_consumer> {
	/// The constructor from the runtime. This fetches the rocket_subsystem
	rocket_input_consumer(runtime* run) : input_consumer{run}
	{
		m_context = run->get_subsystem<rocket_subsystem>()->m_context;
	}
	/// The handle that gets called from `input_consumer`
	bool handle_input(const input_event& event);

	/// Give rocket input focus
	void steal_input() { input_consumer::steal_input(); }
	/// The Rocket context
	Rocket::Core::Context* m_context;
};
}

#endif  // GE_ROCKET_INPUT_CONSUMER_HPP
