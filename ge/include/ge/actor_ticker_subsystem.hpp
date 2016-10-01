#ifndef GE_ACTOR_TICKER_SUBSYSTEM_HPP
#define GE_ACTOR_TICKER_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"
#include "ge/tickable.hpp"
#include "ge/runtime.hpp"

namespace ge
{
struct actor_ticker_subsystem : subsystem {
	struct config {
	};

	bool initialize(config){};
	virtual bool update(std::chrono::duration<float> delta) override
	{
		m_runtime->get_root_actor()->propagate_to_children([delta](actor& act) {
			if (act.implements_interface<tickable>()) {
				act.get_interface_storage<tickable>()->tickfunc(delta);
			}
		});
	}
};
}

#endif  // GE_ACTOR_TICKER_SUBSYSTEM_HPP
