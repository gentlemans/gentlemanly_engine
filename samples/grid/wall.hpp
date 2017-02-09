#pragma once

#ifndef WALL_HPP
#define WALL_HPP

#include "piece.hpp"
#include "gridtick_interface.hpp"


#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>

class wall : public piece
{
	ge::mesh_actor* mesh;
	
public:
	void damage(double damage, piece* calling) override;
	void initialize(glm::uvec2 location);
	void calculate_upgrades() override;
	void tick_grid();
};

#endif  // TURRET_HPP
