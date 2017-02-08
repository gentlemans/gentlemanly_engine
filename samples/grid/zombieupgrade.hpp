#pragma once
#include "piece.hpp"


class zombieupgrade : public piece
{
	void initialize(glm::ivec3 location)
	{
		piece::initialize(location);
		set_upgrade("Max Speed Up", 1);
		//increases the maximum base action speed of the zombies, should be used VERY liberally
		set_upgrade("Minimum Speed Up", 1);
		//increases the minimum speed that zombies can have
		set_upgrade("Max Damage Up", 1);
		//increases the maximum damage of zombies
		set_upgrade("Max Health Up", 1);
		//increases the maximum amount of health that zombies can start with
		set_upgrade("Minimum Health Up", 1);
		//increases the minimum health that zombies can have
		
	}
};