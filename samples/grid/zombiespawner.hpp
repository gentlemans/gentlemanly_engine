#pragma once

#ifndef ZOMBIESPAWNER_HPP
#define ZOMBIESPANWER_HPP

#include "piece.hpp"

#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/texture_asset.hpp>

class zombiespawner : public piece
{
	ge::mesh_actor* mesh;

public:
	void initialize(glm::uvec3 location)
	{
		piece::initialize(location);

		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		mesh->m_mesh_settings.m_material.set_parameter("Texture", m_runtime->m_asset_manager.get_asset<ge::texture_asset>("zombiespawner.texture"));

	}
};

#endif  // ZOMBIESPAWNER_HPP
