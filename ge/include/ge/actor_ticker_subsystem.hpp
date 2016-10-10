#ifndef GE_ACTOR_TICKER_SUBSYSTEM_HPP
#define GE_ACTOR_TICKER_SUBSYSTEM_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/runtime.hpp"
#include "ge/subsystem.hpp"
#include "ge/tickable.hpp"

namespace ge
{
/// Subsystem to allow for actors that implement the tickable interface to get a callback each frame
struct actor_ticker_subsystem : subsystem {
	/// No config required
	struct config {
	};

	/// No init requried
	bool initialize(config) { return true; };
	/// Tick function--this calls each actor's tick function
	virtual bool update(std::chrono::duration<float> delta) override
	{
		m_runtime->get_root_actor()->propagate_to_children([delta](actor& act) {
			if (act.implements_interface<tickable>()) {
				act.get_interface_storage<tickable>()->tickfunc(delta);
			}
		});

		return true;
	}
};
}

#endif  // GE_ACTOR_TICKER_SUBSYSTEM_HPP
