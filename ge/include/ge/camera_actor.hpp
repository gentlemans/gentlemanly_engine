#ifndef GE_CAMERA_ACTOR_HPP
#define GE_CAMERA_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/ortho2d.hpp"
#include "ge/renderable.hpp"

namespace ge
{
/// An actor that represents the place the viewer can see from.
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

		// TODO: fix
		root.propagate_to_children([&vp](actor& act) {
			if (act.implements_interface<renderable>()) {
				act.get_interface_storage<renderable>()->renderfunc(vp);
			}
		});
	}
};
}

#endif  // GE_CAMERA_ACTOR_HPP
