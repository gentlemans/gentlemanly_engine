#pragma once
#include "piece.hpp"


class zombieupgrade : public piece
{
	void initialize()
	{
		piece::initialize({ -2,-2,12 });
		set_upgrade("Speed Up", 1);
		//increases the base action speed of the zombies
	}
};