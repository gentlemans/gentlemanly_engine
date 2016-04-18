#pragma once

#include <glm/glm.hpp>

#include <Box2D/Box2D.h>

namespace ge
{
class physics_controller;

class collision_body
{
	physics_controller* m_controller;

	b2Fixture* m_fixture;

public:
	// box
	collision_body(physics_controller& phys_controlle, glm::vec2 size);

	// circle
	collision_body(physics_controller& phys_controller, float radius);

	// custom
	collision_body(physics_controller& phys_controller, glm::vec2* points, size_t num_points);

	~collision_body();
};
}
