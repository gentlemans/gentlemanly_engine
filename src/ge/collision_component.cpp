#include "ge/collision_component.hpp"
#include "ge/transform_component.hpp"

namespace ge
{
collision_component::collision_component(ge::transform_component& trans, glm::vec2 size)
{
	b2PolygonShape shape;
	auto tmp_vec = trans.get_relative_transform().location;
	shape.SetAsBox(size.x / 2.f, size.y / 2.f, {tmp_vec.x, tmp_vec.y},
		trans.get_relative_transform().rotation);

	b2FixtureDef def;
	def.shape = &shape;
	def.userData = this;

	trans.m_b2_body->CreateFixture(&def);
}

collision_component::collision_component(ge::transform_component& trans, float radius)
{
	b2CircleShape shape;
	auto tmp_vec = trans.get_relative_transform().location;
	shape.m_radius = radius;
	shape.m_p = {tmp_vec.x, tmp_vec.y};

	b2FixtureDef def;
	def.shape = &shape;
	def.userData = this;

	trans.m_b2_body->CreateFixture(&def);
}

}  // namespace ge
