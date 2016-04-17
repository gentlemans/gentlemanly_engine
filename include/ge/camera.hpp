#pragma once

#include "ge/actor.hpp"

namespace ge
{
class camera : public actor
{
public:
	camera(world& world, actor* parent) : actor(world, parent) {}
	float vertical_units = 10.f;

	~camera() = default;
};
}
