#ifndef GE_MESH_ACTOR_HPP
#define GE_MESH_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"
#include "ge/mesh_settings.hpp"

#include <glm/glm.hpp>

namespace ge
{
struct mesh_actor : actor {
	void initialize(mesh_settings settings) { m_mesh_settings = std::move(settings); }
	/// Load from a mesh_asset path
	/// \param asset_path The path to a mesh_asset_settings asset
	void initialize(const char* asset_path);

	mesh_settings m_mesh_settings;

	virtual void render(const glm::mat3& vp_mat) override;
};
}

#endif
