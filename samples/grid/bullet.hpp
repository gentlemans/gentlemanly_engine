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

	bool hit = false;
	int b_range = 0;
	int moves = 0;

	void initialize(glm::uvec2 location, Directions direction, stats stat, int range)
	{
		piece::initialize({ location.x, location.y, 2 });
		rotate(direction);
		now = stat;
		b_range = range;
		add_interface<bullet, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "bullet/bullet.meshsettings").get();

	}
	bool colision_check()
	{
		
	}
	void tick_grid()
	{
		if (countdown_to_action > 0)
		{
			countdown_to_action--;
			return;
		}
		
	}
};

#endif  // TURRET_HPP
