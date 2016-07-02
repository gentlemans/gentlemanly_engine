#ifndef GE_CAMERA_ACTOR_HPP
#define GE_CAMERA_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/ortho2d.hpp"

namespace ge
{
struct camera_actor : actor {
	void initialize(float arg_vert_units) { m_vertical_units = arg_vert_units; }
	float m_vertical_units;

	void render_actors(actor& root, float aspect)
	{
		glm::mat3 p = glm::ortho2d(-aspect * m_vertical_units, aspect * m_vertical_units,
			-m_vertical_units, m_vertical_units);
		glm::mat3 v = calculate_model_matrix();

		glm::mat3 vp = p * v;

		root.propagate_to_children([&vp](actor& act) { act.render(vp); });
	}
};
}

#endif // GE_CAMERA_ACTOR_HPP
