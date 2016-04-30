#pragma once

#include <glm/glm.hpp>

#include <Box2D/Box2D.h>

#include <anax/Component.hpp>

#include <boost/concept_check.hpp>

#include <algorithm>

#include "ge/transform_component.hpp"

namespace ge
{
class transform_component;

struct collison_component : public anax::Component
{
	// box
	collison_component(transform_component& trans, glm::vec2 size);

	// circle
	collison_component(transform_component& trans, float radius);

	// custom poly
	template <typename InputIterator>
	collison_component(transform_component& trans, InputIterator begin, InputIterator end)
	{
		BOOST_CONCEPT_ASSERT((boost::InputIterator<InputIterator>));
		static_assert(
			std::is_same<std::remove_const_t<std::decay_t<decltype(*begin)>>, glm::vec2>::value,
			"collison_component::collison_component custom poly constructor expects an "
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

		trans.body->CreateFixture(&def);
	}

	b2Fixture* m_fixture;
};
}
