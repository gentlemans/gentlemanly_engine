#pragma once

#include "ge/actor.hpp"
#include "ge/physics_world.hpp"

#include <Box2D/Box2D.h>


namespace ge  {

class collision : public actor
{
	b2Body* body;
public:
	collision(actor* owner, const b2BodyDef& body_def, physics_world& world)
		:actor(owner)
	{
		body = world.world->CreateBody(&body_def);
	}
	
	
	
	
};

}
