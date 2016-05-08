#pragma once

#include <entityx/entityx.h>

#include "ge/model_system.hpp"
#include "ge/physics_system.hpp"

namespace ge
{
struct world : entityx::EntityX
{
	world()
	{
		systems.add<model_system>(16.f / 9.f);  // TODO: fix
		systems.add<physics_system>();
		systems.configure();
	}

	void update(double dt) { systems.update_all(dt); }
private:
	std::vector<std::function<void()>> update_callbacks;
};
}
