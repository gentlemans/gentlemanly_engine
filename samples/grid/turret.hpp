#pragma once

#ifndef TURRET_HPP
#define TURRET_HPP

#include "piece.hpp"
#include "gridtick_interface.hpp"


#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class turret : public piece
{
	ge::mesh_actor* mesh;

	boost::signals2::scoped_connection die_connect;

	std::array<int, 1> upgrades;
public:
	void damage(double damage, piece* calling) override
	{
		modify_health(-damage);
	}
	void calculate_upgrades() override;
	void initialize(glm::uvec2 location, Directions direction);
	void tick_grid();
	int hitStreak = 0;
	void shoot();
};

#endif  // TURRET_HPP
