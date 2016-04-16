#include "ge/physics_world.hpp"

#include "ge/collision.hpp"

#include <Box2D/Box2D.h>

#include <memory>

namespace ge
{
physics_world::physics_world(glm::vec2 gravity)
{
	world = std::make_unique<b2World>(b2Vec2{gravity.x, gravity.y});
}
}
