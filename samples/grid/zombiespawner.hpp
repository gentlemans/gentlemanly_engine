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
	void initialize(glm::uvec2 location)
	{
		piece::initialize({location.x, location.y, 2});

		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		mesh->set_mat_param("Texture", get_asset<ge::texture_asset>("zombiespawner.texture"));

	}
};

#endif  // ZOMBIESPAWNER_HPP
