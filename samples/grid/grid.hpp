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

	std::vector<piece*> get_actors_at_coord(glm::ivec3 loc);
	
	/// Check if there's stuff around a certain location
	/// \param location The location to check around
	/// \param level The level to try to detect things on
	/// \return The four directions use vec[piece::NORTH], vec[piece::EAST] etc.
	std::array<std::vector<piece*>, 4> check_squares_around(glm::ivec2 location, int level = 2);

	
	std::vector<std::vector<piece*>> squares_in_direction(
		glm::ivec2 myLocation, piece::Directions direction, int range);


	
	piece::stats get_z_stats();
	void try_spawn_z();

	glm::ivec2 get_size() { return m_size; }
	void increment_z_count(bool positive);
	int get_z_count();

	static grid* instance;
};

	
glm::ivec2 get_location_from_direction(glm::ivec2 starting, piece::Directions direction, int distance);

