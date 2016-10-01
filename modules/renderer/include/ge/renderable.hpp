#ifndef GE_RENDERABLE_HPP
#define GE_RENDERABLE_HPP

#pragma once

#include <functional>
#include <memory>

namespace ge
{
struct renderable {
	struct interface_storage {
		interface_storage(std::function<void(const glm::mat3&)> arg) : renderfunc(std::move(arg)) {}
		std::function<void(const glm::mat3&)> renderfunc;
	};

	template <typename ActorType>
	static std::shared_ptr<interface_storage> gen_interface(ActorType* act)
	{
		return std::make_shared<interface_storage>(
			[act](const glm::mat3& arg) { act->render(arg); });
	}
};
}

#endif  // GE_RENDERABLE_HPP
