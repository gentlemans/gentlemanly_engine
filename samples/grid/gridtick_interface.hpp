#ifndef GE_GRIDTICK_INTERFACE_HPP
#define GE_GRIDTICK_INTERFACE_HPP

#pragma once

#include <functional>
#include <vector>
#include <memory>

#include "ge/actor.hpp"

struct gridtick_interface {
	struct interface_storage {
		interface_storage(const std::function<void()> call) : callback(call) {}
		std::function<void()> callback;
	};
	
	std::vector<std::weak_ptr<ge::actor>> attached; 
	
	template <typename ActorType>
	std::shared_ptr<interface_storage> gen_interface(ActorType* act)
	{
		attached.push_back(ge::actor::shared(act));
		
		return std::make_shared<interface_storage>([act]() {

			// If you get an error here, then you need to define the tick_grid function
			act->tick_grid();
		});
	}
};

#endif  // GE_GRIDTICK_INTERFACE_HPP
