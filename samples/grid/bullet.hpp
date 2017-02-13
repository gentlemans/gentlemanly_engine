#pragma once

#ifndef BULLET_HPP
#define BULLET_HPP

#include "gridtick_interface.hpp"
#include "piece.hpp"

#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class bullet : public piece
{
	ge::mesh_actor* mesh;

	boost::signals2::scoped_connection die_connect;

	std::array<int, 1> upgrades;

public:
	void initialize(glm::uvec2 location, Directions direction, stats stat)
	{
		piece::initialize({ location.x, location.y, 2 });
		rotate(direction);
		now = stat;
		add_interface<turret, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();

	}
	void tick_grid();
};

#endif  // TURRET_HPP
