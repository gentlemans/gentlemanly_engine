#ifndef GE_TICKABLE_HPP
#define GE_TICKABLE_HPP

#pragma once

#include <functional>
#include <memory>
#include <chrono>

namespace ge {

// Actor interface to get a tick callback
struct tickable {
	
	struct interface_storage {
		interface_storage(std::function<void(std::chrono::duration<float>)> func) : tickfunc(std::move(func)) {}
		std::function<void(std::chrono::duration<float>)> tickfunc;
	};
	
	template<typename ActorType>
	static std::shared_ptr<interface_storage> gen_interface(ActorType* actor) {
		return std::make_shared<interface_storage>([actor](std::chrono::duration<float> delta) {
			actor->tick(delta);
		});
	}
	
};

}

#endif // GE_TICKABLE_HPP
