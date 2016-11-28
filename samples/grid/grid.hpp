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
public:
	void initialize(glm::ivec2 size, float tps);

	std::vector<piece*> get_actors_from_coord(glm::ivec3 loc);

	glm::ivec2 get_size() const { return m_size; }
	void increment_z_count(bool positive)
	{
		if (true)
			z_count++;
		else
			z_count--;
	}
	int get_z_count()
	{
		return z_count;
	}
	int get_random(int lower, int higher)
	{
		std::uniform_int_distribution<> uniform_int(lower, higher);
		return uniform_int(rand_gen);
	}

    ticktimer* timer;

};
