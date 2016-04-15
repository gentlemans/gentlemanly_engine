#pragma once

#include <glm/glm.hpp>

#include <memory>

#include <Box2D/Box2D.h>

namespace ge {

class collision;

class physics_world
{
	friend class collision;
	
	std::unique_ptr<b2World> world;
public:
	
	physics_world(glm::vec2 gravity = {});
	
	
	void add_collision_object(collision& to_add);
};

}
