#pragma once

#include "ge/actor.hpp"

#include "ge/physics_world.hpp"

#include <Box2D/Box2D.h>

namespace ge
{
class collision : public actor
{
	b2Body* m_body;

public:
	collision(world& world, actor* owner, physics_world& phys_world, const b2BodyDef& body_def)
		: actor(world, owner)
	{
		m_body = phys_world.world->CreateBody(&body_def);
	}
};
}
