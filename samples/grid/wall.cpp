#include "wall.hpp"

void wall::calculate_upgrades(const std::string & name)
{
	now = initial;
	if (name == "Speed Up")
	{
		now.speed = now.speed - (2 * get_upgrade(name));
		if (now.speed > 0)
			now.speed = 0;
		return;
	}
	if (name == "Hp Up")
	{
		now.health = now.health + (100 * get_upgrade(name));
		return;
	}

	set_upgrade("Regen Up", 5);
	//Adds 5 helth points regenerated per tick, given on peice action
	set_upgrade("Barbed Wire", 1);
}
