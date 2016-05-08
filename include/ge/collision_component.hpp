#pragma once

#include <glm/glm.hpp>

#include <Box2D/Box2D.h>

#include <boost/concept_check.hpp>

#include <algorithm>

#include "ge/transform_component.hpp"

namespace ge
{
class transform_component;

struct collision_component
{
	// box
	collision_component(transform_component& trans, glm::vec2 size);

	// circle
	collision_component(transform_component& trans, float radius);

	// custom poly
	template <typename InputIterator>
	collision_component(transform_component& trans, InputIterator begin, InputIterator end)
	{
		BOOST_CONCEPT_ASSERT((boost::InputIterator<InputIterator>));
		static_assert(
			std::is_same<std::remove_const_t<std::decay_t<decltype(*begin)>>, glm::vec2>::value,
			"collision_component::collision_component custom poly constructor expects an "
			"InputIterator that dereferences to a glm::vec2");

		auto entity_loc = trans.get_relative_transform().location;

		std::vector<glm::vec2> offsetted(std::distance(begin, end));
		std::transform(begin, end, offsetted.begin(), [entity_loc](glm::vec2& loc)
			{
				return loc + entity_loc;
			});

		b2PolygonShape shape;
		shape.Set((b2Vec2*)offsetted.data(), offsetted.size());

		b2FixtureDef def;
		def.shape = &shape;
		def.userData = this;

		trans.m_b2_body->CreateFixture(&def);
	}

	b2Fixture* m_fixture;
};
}
