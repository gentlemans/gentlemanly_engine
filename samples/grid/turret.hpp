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
		initial.damage = 50;
		initial.health = 100;
		now.health = 100;
		now.speed = 4;
		set_upgrade("Attack Speed Up", 1);
		set_upgrade("Damage Up", 1);
		set_upgrade("Regen Up", 1);
		die_connect = sig_die.connect([](piece* p) {
			p->set_parent(NULL);
		});
	}
	void calculate_upgrades(const std::string& name) override
	{
		if (name == "Attack Speed Up")
		{
			int amount = get_upgrade(name);
			if (amount < 0)
				return;
			now.speed = initial.speed;
			for (int x = 0; x < amount; x++)
			{
				now.speed -= 2;
				if (now.speed > 0)
				{
					now.speed = 0;
				}
			}
		}
		if (name == "Damage Up")
		{
			int amount = get_upgrade(name);
			if (amount < 0)
				return;
			now.damage = initial.damage;
			for (int x = 0; x < amount; x++)
			{
				now.damage = now.damage*1.1;
			}
		}
		if (name == "Regen Up")
		{
			int amount = get_upgrade(name);
			if (amount < 0)
				return;
			now.regen = initial.regen;
			for (int x = 0; x < amount; x++)
			{
				now.regen += 1;
			}
		}
		return;
	}
	void tick_grid()
    {  
		if (countdown_to_action >= 0)
		{
			countdown_to_action--;
			return;
		}
		else
			countdown_to_action = now.speed;
		shoot();
		modify_health(-now.regen*(now.speed+1));
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
