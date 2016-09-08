#ifndef GE_MESH_ACTOR_HPP
#define GE_MESH_ACTOR_HPP

#pragma once

#include "ge/actor.hpp"

#include <glm/glm.hpp>

namespace ge
{
class mesh;
class material;

struct mesh_actor : actor {
	void initialize(const std::shared_ptr<mesh>& arg_mesh) { m_mesh = arg_mesh; }
	/// Load from a mesh_asset path
	/// \param asset_path The path to a mesh_asset asset
	void initialize(const char* asset_path);

	std::shared_ptr<mesh> m_mesh;

	virtual void render(const glm::mat3& vp_mat) override;
};
}

#endif
