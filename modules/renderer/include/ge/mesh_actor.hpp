#ifndef GE_MESH_ACTOR_HPP
#define GE_MESH_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/mesh_settings.hpp"
#include "ge/renderable.hpp"

#include <glm/glm.hpp>

namespace ge
{
/// A super basic actor that draws a mesh at it's location. Try to avoid derriving from it, just put
/// a mesh as a child of your own actor.
/// This helps keep hierarchies shallow and eaiser to understand.
struct mesh_actor : actor {
	/// Initialize the mesh_actor
	/// \param settings The `mesh_settings` object to copy from
	void initialize(mesh_settings settings)
	{
		m_mesh_settings = std::move(settings);
		add_interface<mesh_actor, renderable>();
	}
	/// Load from a mesh_asset path
	/// \param asset_path The path to a mesh_asset_settings asset
	void initialize(const char* asset_path);

	/// The `mesh_settings` for the actor to draw
	mesh_settings m_mesh_settings;

	/// Implementation of the actor's rendering interface
	void render(const glm::mat3& vp_mat);
};
}

#endif
