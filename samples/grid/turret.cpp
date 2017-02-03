#include "turret.hpp"

void turret::calculate_upgrades(const std::string & name)
{
	now = initial;
	if (name == "Attack Speed Up")
	{
		now.speed =now.speed - (2*get_upgrade(name));
		if (now.speed > 0)
			now.speed = 0;
		return;
	}
	if (name == "Damage Up")
	{
		int amount = get_upgrade(name);
		if (amount < 0)
			return;
		for (int x = 0; x < amount; x++)
		{
			now.damage = now.damage*1.1;
		}
	}
	if (name == "Regen Up")
	{
		now.regen = now.regen + (get_upgrade(name) * 2);
		return;
	}
	return;
}
