#include "wall.hpp"

void wall::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (2 * get_upgrade("Speed Up"));
	now.health = now.health + (100 * get_upgrade("Hp Up"));
	set_upgrade("Regen Up", 5);
	//Adds 5 helth points regenerated per tick, given on peice action
	set_upgrade("Barbed Wire", 1);
	if (now.speed > 0)
		now.speed = 0;
}
