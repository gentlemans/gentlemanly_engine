#ifndef GE_CAMERA_ACTOR_HPP
#define GE_CAMERA_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/ortho2d.hpp"

namespace ge
{
struct camera_actor : actor {
	/// Initialize function for the actor
	/// \param arg_vert_units The nubmer of vertical units to be visible on the screen
	void initialize(float arg_vert_units) { m_vertical_units = arg_vert_units; }
	/// The nubmer of vertical units to display on the screen
	float m_vertical_units;

	/// Call this to render all actors under a root actor with a given aspect ratio
	/// This is usually called by sdl_subsystem.
	/// \param root The root actor. All children actors under this will be rendered.
	/// \param aspect The aspect ratio for the screen
	void render_actors(actor& root, float aspect)
	{
		glm::mat3 p = glm::ortho2d(-aspect * m_vertical_units / 2.f,
			aspect * m_vertical_units / 2.f, -m_vertical_units / 2.f, m_vertical_units / 2.f);
		glm::mat3 v = calculate_model_matrix();

		glm::mat3 vp = p * v;

		root.propagate_to_children([&vp](actor& act) { act.render(vp); });
	}
};
}

#endif  // GE_CAMERA_ACTOR_HPP
