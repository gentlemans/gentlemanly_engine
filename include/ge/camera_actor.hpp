#pragma once

#include "ge/actor.hpp"

namespace ge
{
class camera_actor : public actor
{
public:
	camera_actor(world& world, actor* parent) : actor(world, parent) {}
	float vertical_units = 10.f;

	~camera_actor() = default;
};
}
