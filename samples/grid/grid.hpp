#pragma once

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>

#include <memory>
#include <random>
#include <vector>

#include "ticktimer.hpp"

class piece;

class grid : public ge::actor
{
	glm::ivec2 m_size;
	std::mt19937 rand_gen;
	unsigned int z_count=0;
	unsigned int max_z = 5;
	const int z_spawn_delay = 1;
	bool spawning = false;
public:
	ticktimer* timer;
	int get_random(int lower, int higher)
	{
		std::uniform_int_distribution<> uniform_int(lower, higher);
		return uniform_int(rand_gen);
	}
private:
	void try_spawn_z()
	{
		if (z_count < max_z && spawning == false)
		{
			int x;
			int y;
			int bool1 = get_random(0, 1); //choses if the zombie will be spawned on x or y axis
			int bool2 = get_random(0, 1); // choses if the zombie will be top or bottom/left or right
			int position = get_random(0, 10); // choses where on that row/collumn the zombie will be spawned
			if (bool1 == 1)
			{
				if (bool2 == 1)
					x = -1;
				else
					x = 11;
				y = position;
			}
			else
			{
				if (bool2 == 1)
					y = -1;
				else
					y = 11;
				x = position;
			}
		}
		else
			spawning = false;
	}
public:
	void initialize(glm::ivec2 size, float tps);

	std::vector<piece*> get_actors_from_coord(glm::ivec3 loc);

	glm::ivec2 get_size() { return m_size; }
	void increment_z_count(bool positive)
	{
		if (positive)
			z_count++;
		else
		{
			z_count--;
			try_spawn_z();
		}
	}
	int get_z_count()
	{
		return z_count;
	}


    

};
