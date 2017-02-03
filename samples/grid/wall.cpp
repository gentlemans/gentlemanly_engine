#include "wall.hpp"

void wall::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (2 * get_upgrade("Speed Up"));
	now.health = now.health + (100 * get_upgrade("Hp Up"));
	now.regen= now.regen+get_upgrade("Regen Up")*100;
	if (now.speed > 0)
		now.speed = 0;
}
