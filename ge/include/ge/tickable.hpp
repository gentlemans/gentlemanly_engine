#ifndef GE_TICKABLE_HPP
#define GE_TICKABLE_HPP

#pragma once

#include <chrono>
#include <functional>
#include <memory>

namespace ge
{
/// Actor interface to get a tick callback
/// Requires a `tick` function in the actor that takes in a std::chrono::duration<float>. 
struct tickable {
	
	/// The interface storage for tickables, this is handled by tickable, don't worry about it
	struct interface_storage {
		/// Constructor so it can be used with std::make_shared
		/// \param func The function object
		interface_storage(std::function<void(std::chrono::duration<float>)> func)
			: tickfunc(std::move(func))
		{
		}

		/// The tick function object
		std::function<void(std::chrono::duration<float>)> tickfunc;
	};

	/// The interface generation function. Generates a interface_storage object
	/// \param actor The actor object to generate the interface for
	/// \return The generated interface_storage object
	template <typename ActorType>
	static std::shared_ptr<interface_storage> gen_interface(ActorType* actor)
	{
		return std::make_shared<interface_storage>(
			// if you get an error here, you need to implement a tick function
			// in your actor that has the parameter std::chrono::duration<float>
			// so it looks like this: void tick(std::chrono::duration<float> delta)
			[actor](std::chrono::duration<float> delta) { actor->tick(delta); });
	}
};
}

#endif  // GE_TICKABLE_HPP
