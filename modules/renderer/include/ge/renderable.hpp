#ifndef GE_RENDERABLE_HPP
#define GE_RENDERABLE_HPP

#pragma once

#include <functional>
#include <memory>

namespace ge
{

/// Actor interface for actors that want to create their own OpenGL calls.
/// Requries a render(const glm::mat3& vp) function in the actor
struct renderable {

	/// Interface storage, handled by renderable. 
	struct interface_storage {

		/// Constructor so make_shared can be used
		/// \param arg The func
		interface_storage(std::function<void(const glm::mat3&)> arg) : renderfunc(std::move(arg)) {}

		/// The render function object
		std::function<void(const glm::mat3&)> renderfunc;
	};

	/// The interface generation function
	/// \param act The actor pointer
	template <typename ActorType>
	static std::shared_ptr<interface_storage> gen_interface(ActorType* act)
	{
		/// If you get an error here, you need to implement a render 
		/// function with the signature: void render(const glm::mat3& vp)
		return std::make_shared<interface_storage>(
			[act](const glm::mat3& arg) { act->render(arg); });
	}
};
}

#endif  // GE_RENDERABLE_HPP
