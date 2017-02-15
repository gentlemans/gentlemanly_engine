#pragma once

#include <ge/asset_manager.hpp>
#include <ge/material.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/mesh_asset.hpp>
#include <ge/mesh_settings_asset.hpp>
#include <ge/runtime.hpp>
#include <ge/texture_asset.hpp>

#include "piece.hpp"

class base : public piece
{
public:
	std::shared_ptr<ge::mesh_actor> m_mesh;

	void initialize(glm::ivec2 loc)
	{
		piece::initialize({loc.x, loc.y, 2});

		m_mesh = ge::actor::factory<ge::mesh_actor>(this, "texturedmodel/textured.meshsettings");
		m_mesh->set_mat_param("Texture", get_asset<ge::texture_asset>("base_texture"));
	}
};
