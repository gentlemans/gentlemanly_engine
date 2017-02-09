#pragma once

#include <ge/actor.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/texture_asset.hpp>
#include <ge/shader_asset.hpp>
#include <ge/material_asset.hpp>
#include "grid.hpp"
#include "gridtick_interface.hpp"
#include "piece.hpp"

class zombie : public piece
{
	glm::ivec2 get_grid_center() { return {m_grid->get_size().x / 2, m_grid->get_size().y / 2}; }
	void damage_in_direction(Directions d);
	bool attacking;
	double Calculate_Resources();
public:
	ge::mesh_actor* m_mesh;

	boost::signals2::scoped_connection die_connect;
	boost::signals2::scoped_connection take_damage;
	ge::material zombie_mat;
	ge::material red_mat;

	void initialize(glm::ivec3 location, stats stat);
	void damage(double damage, piece* calling) override
	{
		m_mesh->m_mesh_settings.m_material = red_mat;
		m_grid->timer->add_timer(1, [this] {
			m_mesh->m_mesh_settings.m_material = zombie_mat;
		}, shared(this));
		modify_health(-damage);
	}
	void move_closer_to_center();
	void move_random();
	void move_off_spawner();
	void tick_grid();
};
