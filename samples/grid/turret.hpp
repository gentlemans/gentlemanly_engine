#pragma once

#ifndef TURRET_HPP
#define TURRET_HPP

#include "piece.hpp"

#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class turret : public piece
{
	ge::mesh_actor* mesh;

public:
	void initialize(glm::uvec3 location)
	{
		piece::initialize(location);

		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
	}
};

#endif  // TURRET_HPP
