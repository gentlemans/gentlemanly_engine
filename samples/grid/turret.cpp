#include "turret.hpp"

inline void turret::calculate_upgrades(const std::string & name)
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
