#pragma once

#include <ge/actor.hpp>
#include <ge/material_asset.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/shader_asset.hpp>
#include <ge/texture_asset.hpp>
#include "grid.hpp"
#include "gridtick_interface.hpp"
#include "piece.hpp"

class zombie : public piece
{
	glm::ivec2 get_grid_center() { return {m_grid->get_size().x / 2, m_grid->get_size().y / 2}; }
	void damage_in_direction(Directions d);
	bool attacking;
	double Calculate_Resources();
	bool Check_for_other_zombies(std::vector<piece*> pvec);

public:
	ge::mesh_actor* m_mesh;

	boost::signals2::scoped_connection die_connect;
	boost::signals2::scoped_connection take_damage;
	ge::material zombie_mat;
	ge::material red_mat;
	ge::material dead_mat;

	void initialize(glm::ivec3 location, stats stat);
	void damage(double damage, piece* calling) override;
	void move_closer_to_center();
	void move_random();
	void move_off_spawner();
	void action() override;
};
