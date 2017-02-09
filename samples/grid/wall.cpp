#include "wall.hpp"
#include "connector.hpp"

void wall::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (2 * get_upgrade("Speed Up"));
	now.health = now.health + (100 * get_upgrade("Hp Up"));
	now.regen= now.regen+get_upgrade("Regen Up")*100;
	if (now.speed > 0)
		now.speed = 0;
}

void wall::damage(double damage, piece* calling)
	{
		int x = get_upgrade("Barbed Wire");
		if (x > 0)
		{
			calling->damage(damage*(log(x) / 10 +  x / 100), this);
		}
		modify_health(-damage);
	}

void wall::initialize(glm::uvec2 location)
	{
		piece::initialize({location.x, location.y, 2});
		add_interface<wall, gridtick_interface>();
		mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
		mesh->set_mat_param("Texture", get_asset<ge::texture_asset>("wall.texture"));
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
		
		connect_track(sig_die, [](piece* p) {
			p->set_parent(NULL);
		}, shared(this));
	}

void wall::tick_grid()
	{
		if (countdown_to_action >= 0)
		{
			countdown_to_action--;
			return;
		}
		countdown_to_action = now.speed;
		modify_health(-now.regen);
	}
