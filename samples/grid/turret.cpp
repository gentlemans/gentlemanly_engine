#include "turret.hpp"

void turret::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (2*get_upgrade("Attack Speed Up"));
	if (now.speed > 0)
		now.speed = 0;
	int amount = get_upgrade("Damage Up");
	for (int x = 0; x < amount; x++)
	{
		now.damage = now.damage*1.1;
	}
	now.regen = now.regen + (get_upgrade("Regen Up") * 20);
	return;
}
