#pragma once

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>

#include <memory>
#include <random>
#include <vector>

class piece;

class grid : public ge::actor
{
	glm::uvec2 m_size;
	std::mt19937 rand_gen;

public:
	void initialize(glm::uvec2 size, float tps);

	std::vector<piece*> get_actors_from_coord(glm::uvec3 loc);

	glm::uvec2 get_size() const { return m_size; }
	int get_random(int lower, int higher)
	{
		std::uniform_int_distribution<> uniform_int(lower, higher);
		return uniform_int(rand_gen);
	}
};
