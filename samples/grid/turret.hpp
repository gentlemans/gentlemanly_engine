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
	enum upgradesenum {
		DamagePlus,
		HealthPlus,
		RegenPlus,
	};
	void increment_upgrade(upgradesenum to_increment, bool positive)
	{
		if (positive)
			upgrades[to_increment]++;
		else
			upgrades[to_increment]--;
	}

	void damage(float damage) override
	{
		modify_health(-damage);
	}
	void initialize(glm::uvec3 location, Directions direction)
	{
		rotate(direction);
		piece::initialize(location);
		add_interface<turret, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		now.damage = 50;
		inital.health = 100;
		now.health = 100;
		die_connect = sig_die.connect([](piece* p) {
			p->set_parent(NULL);
		});
	}
	void tick_grid()
    {      
		shoot();
	}
	void shoot()
	{
		int range = 3;
		auto squares = squares_in_direction(get_grid_location(), my_direction, range);
		piece* tod;
		for (int x = 0; x < range; x++)
		{
			if (squares[x].size() != 0)
			{
				tod = squares[x][0];
				break;
			}
			else if (x==range-1)
			{
				return;
			}
		}
		tod->damage(now.damage);
	}
};

#endif  // TURRET_HPP
