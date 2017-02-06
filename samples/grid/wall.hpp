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
	void damage(double damage, piece* calling) override
	{
		modify_health(-damage);
		int x = get_upgrade("Barbed Wire");
		if (x > 0)
		{
			calling->damage(damage*(log(x) / 10 +  x / 100), this);
		}
	}
	void initialize(glm::uvec3 location)
	{
		piece::initialize(location);
		add_interface<wall, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		mesh->m_mesh_settings.m_material.set_parameter("Texture", m_runtime->m_asset_manager.get_asset<ge::texture_asset>("wall.texture"));
		initial.damage = 0;
		initial.health = 1000;
		initial.regen = 5;
		initial.speed = 14;
		now = initial;
		set_upgrade("Speed Up", 1);
		//Increases the action speed of the tower
		set_upgrade("Hp Up", 1);
		//Each upgrade adds a stacking 10% health increase
		set_upgrade("Regen Up", 1);
		//Adds 5 helth points regenerated per tick, given on peice action
		set_upgrade("Barbed Wire", 1);
		//Adds a small amount of damage that zombies take every time they attack you
		die_connect = sig_die.connect([](piece* p) {
			p->set_parent(NULL);
		});
	}
	void calculate_upgrades() override;
	void tick_grid()
	{
		if (countdown_to_action >= 0)
		{
			countdown_to_action--;
			return;
		}
		countdown_to_action = now.speed;
		modify_health(-now.regen);
	}
};

#endif  // TURRET_HPP
