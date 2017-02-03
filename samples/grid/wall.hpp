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
		add_interface<wall, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		initial.damage = 0;
		initial.health = 1000;
		initial.regen = 5;
		initial.speed = 14;
		now = initial;
		set_upgrade("Speed Up", 1);
		//Increases the action speed of the tower
		set_upgrade("Hp Up", 1);
		//Each upgrade adds a stacking 10% health increase
		set_upgrade("Regen Up", 5);
		//Adds 5 helth points regenerated per tick, given on peice action
		set_upgrade("Barbed Wire", 1);
		//Adds a small amount of damage that zombies take every time they attack you
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
		modify_health(-now.regen*(now.speed + 1));
	}
};

#endif  // TURRET_HPP
