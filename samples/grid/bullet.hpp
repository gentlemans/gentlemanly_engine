#pragma once

#ifndef BULLET_HPP
#define BULLET_HPP

#include "gridtick_interface.hpp"
#include "piece.hpp"
#include "zombie.hpp"
#include "connector.hpp"

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
	piece* m_turret;

	void initialize(glm::uvec2 location, Directions direction, stats stat, int range, piece* my_turret)
	{
		piece::initialize({ location.x, location.y, 1 });
		rotate(direction);
		m_turret = my_turret;
		initial = stat;
		initial.speed = 1;
		now = initial;
		b_range = range;

		mesh = ge::actor::factory<ge::mesh_actor>(this, "bullet/bullet.meshsettings").get();

		connect_track(sig_die, [](piece* p) { p->set_parent(NULL); }, shared(this));

	}
	std::vector<piece*> colision_check(glm::ivec2 check_here)
	{
		std::vector<piece*> layer_2 = m_grid->get_actors_at_coord(glm::ivec3(check_here.x, check_here.y, 2));
		std::vector<piece*> colided;
		for (auto item : layer_2)
		{
			if (typeid(*item) != typeid(zombiespawner))
			{
				colided.push_back(item);
			}
		}
		return colided;
	}

	void action() override {

		if (moves >= b_range)
		{
			sig_die(this);
			hit = false;
		}
		moves++;
		auto m_location = get_grid_location();
		std::vector<piece*> colision_vec = colision_check(get_location_from_direction(m_location, get_rotation(), 1));
		if (colision_vec.size() != 0)
			{
				colision_vec[0]->damage(now.damage, m_turret);
				hit = true;
				sig_die(this);
				return;
			}	
		else
			{
				set_grid_location(glm::ivec3(get_location_from_direction(m_location, get_rotation(), 1), level()));
			}
	}
	
};

#endif  // TURRET_HPP
