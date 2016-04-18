#include "ge/collision_body.hpp"
#include "ge/physics_controller.hpp"

namespace ge
{
collision_body::collision_body(physics_controller& phys_controller, glm::vec2 size)
	: m_controller{&phys_controller}
{
	b2PolygonShape shape;
	auto tmp_vec = m_controller->get_actor().calcuate_absolute_location();
	shape.SetAsBox(size.x / 2.f, size.y / 2.f, {tmp_vec.x, tmp_vec.y},
		m_controller->get_actor().calcuate_absolute_rotation());

	b2FixtureDef def;
	def.shape = &shape;
	def.userData = this;

	phys_controller.m_b2_body->CreateFixture(&def);
}

collision_body::collision_body(ge::physics_controller& phys_controller, float radius)
	: m_controller{&phys_controller}
{
	b2CircleShape shape;
	auto tmp_vec = m_controller->get_actor().calcuate_absolute_location();
	shape.m_radius = radius;
	shape.m_p = {tmp_vec.x, tmp_vec.y};

	b2FixtureDef def;
	def.shape = &shape;
	def.userData = this;

	m_controller->m_b2_body->CreateFixture(&def);
}

collision_body::collision_body(
	ge::physics_controller& phys_controller, glm::vec2* points, size_t num_points)
{
	b2PolygonShape shape;
	shape.Set(reinterpret_cast<b2Vec2*>(points), num_points);

	b2FixtureDef def;
	def.shape = &shape;
	def.userData = this;

	m_controller->m_b2_body->CreateFixture(&def);
}

collision_body::~collision_body() { m_controller->m_b2_body->DestroyFixture(m_fixture); }
}  // namespace ge
