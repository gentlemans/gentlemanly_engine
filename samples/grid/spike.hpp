#pragma once

#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "gridtick_interface.hpp"
#include "piece.hpp"

#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/texture_asset.hpp>
#include "grid.hpp"

class spike : public piece
{
	ge::mesh_actor* mesh;

public:
	void initialize(glm::uvec2 location)
	{
		piece::initialize({location.x, location.y, 1});
		add_interface<spike, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		mesh->set_mat_param("Texture", get_asset<ge::texture_asset>("spike.texture"));

		sig_die.connect([](piece* p) { p->set_parent(NULL); });
	}
	void tick_grid()
	{
		if (countdown_to_action >= 0) {
			countdown_to_action--;
			return;
		} else
			countdown_to_action = now.speed;
		glm::ivec3 myLocation = get_grid_location();
		auto actors = m_grid->get_actors_from_coord(glm::ivec3(myLocation.x, myLocation.y, 2));
		for (int x = 0; x < actors.size(); x++) {
			actors[x]->damage(3, this);
		}
	}
};

#endif  // TURRET_HPP
