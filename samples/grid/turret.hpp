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
	void damage(double damage) override
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
		//Increases the action speed of the tower
		set_upgrade("Damage Up", 1);
		//Each upgrade adds a stacking 10% damage increase
		set_upgrade("Regen Up", 1);
		//Adds one helth point regenerated per tick, given on peice action
		set_upgrade("Increaded Accuracy", 1);
		//Adds a stacking 10% increase to speed up to a total of 33% for each shot the turret doesn't miss
		die_connect = sig_die.connect([](piece* p) {
			p->set_parent(NULL);
		});
	}
	void calculate_upgrades(const std::string& name) override;
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
	int hitStreak = 0;
	void shoot()
	{
		int range = 3;
		auto squares = squares_in_direction(get_grid_location(), my_direction, range);
		piece* tod;
		for (int x = 0; x < range; x++)
		{
			if (squares[x].size() != 0)
			{
				if(hitStreak < 3)
					hitStreak++;
				tod = squares[x][0];
				break;
			}
			else if (x==range-1)
			{
				hitStreak = 0;
				return;
			}
		}
		double calculated_damage = now.damage*pow(1.1,hitStreak);
		tod->damage(calculated_damage);
	}
};

#endif  // TURRET_HPP
