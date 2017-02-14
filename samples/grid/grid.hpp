#pragma once

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>

#include <memory>
#include <random>
#include <vector>

#include "ticktimer.hpp"
#include "zombiespawner.hpp"
#include "zombieupgrade.hpp"

class piece;

class grid : public ge::actor
{
	glm::ivec2 m_size;
	double resources = 0;
	unsigned int z_count = 0;
	unsigned int max_z = 5;
	const int z_spawn_delay = 1;
	bool spawning = false;

public:
	std::mt19937 rand_gen;
	ticktimer* timer;
	int get_random(int lower, int higher);
	double get_random(double lower, double higher);
	double get_resources() { return resources; }
	void change_resources(double amount) { resources = resources + amount; }
	void initialize(glm::ivec2 size, float tps);

	std::vector<piece*> get_actors_from_coord(glm::ivec3 loc);

	piece::stats get_z_stats();
	void try_spawn_z();

	glm::ivec2 get_size() { return m_size; }
	void increment_z_count(bool positive);
	int get_z_count();

	static grid* instance;
};
