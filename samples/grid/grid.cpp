#include "grid.hpp"

#include "base.hpp"
#include "zombie.hpp"

#include <ge/runtime.hpp>
#include <ge/timer_subsystem.hpp>

#include "gridtick_interface.hpp"

grid* grid::instance = nullptr;

void grid::initialize(glm::ivec2 size, float tps)
{
	   instance = this;

	// the 0.5 is because the locations are the centers, so we need to account for that
	set_relative_location(glm::vec2(-float(size.x) / 2.f + 0.5, -float(size.y) / 2.f + 0.5));

	m_size = size;

	auto b = ge::actor::factory<base>(this, size / 2);

	auto timersub = m_runtime->get_subsystem<ge::timer_subsystem>();

	auto func = [this] {

		auto* interface = m_runtime->get_interface<gridtick_interface>();

		assert(interface);

		for (auto id = 0ull; id != interface->attached.size();
			/*don't ++ here because if we delete we don't want to*/) {
			auto& weakActor = interface->attached[id];
			if (weakActor.expired()) {
				interface->attached.erase(interface->attached.begin() + id);
			} else {
				weakActor.lock()->get_interface_storage<gridtick_interface>()->callback();
				++id;
			}
		}

		// actor::factory<zombie>(this, glm::ivec3{get_random(0, 10), get_random(0, 10), 2});
	};

	timersub->add_timer(func, std::chrono::duration<float>(std::chrono::seconds(1)) / tps, true);

	timer = ge::actor::factory<ticktimer>(this).get();
}
std::vector<piece*> grid::get_actors_at_coord(glm::ivec3 loc)
{
	std::vector<piece*> ret;

	for (auto& child : m_children) {
		piece* p = dynamic_cast<piece*>(child.get());
		if (!p) continue;

		if (p->get_grid_location() == loc) {
			ret.push_back(p);
		}
	}

	return ret;
}


std::vector<piece*> grid::get_actors_at_coord(glm::ivec2 loc) {
	std::vector<piece*> ret;

	for (auto& child : m_children) {
		piece* p = dynamic_cast<piece*>(child.get());
		if (!p) continue;

		if (p->get_grid_location().x == loc.x && p->get_grid_location().y == loc.y) {
			ret.push_back(p);
		}
	}

	return ret;
}


std::array<std::vector<piece*>, 4> grid::check_squares_around(glm::ivec2 myLocation, int level)
{
	std::array<std::vector<piece*>, 4> emptySquares;

	emptySquares[piece::NORTH] = get_actors_at_coord({myLocation.x, myLocation.y + 1, level});
	emptySquares[piece::WEST] = get_actors_at_coord({myLocation.x - 1, myLocation.y, level});
	emptySquares[piece::SOUTH] = get_actors_at_coord({myLocation.x, myLocation.y - 1, level});
	emptySquares[piece::EAST] = get_actors_at_coord({myLocation.x + 1, myLocation.y, level});

	return emptySquares;
}


std::vector<std::vector<piece*>> grid::squares_in_direction(
	glm::ivec2 starting, piece::Directions direction, int range)
{
	std::vector<std::vector<piece*>> squares;
	squares.reserve(range);
	for (int x = 0; x < range; x++) {
		starting = get_location_from_direction(starting, direction, 1);
		
		squares.push_back(get_actors_at_coord(glm::ivec3(starting.x, starting.y, 2)));
	}
	return squares;
}


piece::stats grid::get_z_stats()
{
	std::vector<piece*> upgradesvec = get_actors_at_coord(glm::ivec3(-2, -2, -2));
	piece* upgrades = upgradesvec[0];
	double mn_h = upgrades->get_upgrade("Minimum Health Up");
	double mx_h = upgrades->get_upgrade("Max Health Up");
	double mx_s = upgrades->get_upgrade("Max Speed Up");
	double mn_s = upgrades->get_upgrade("Minimum Speed Up");
	double mx_d = upgrades->get_upgrade("Max Damage Up");
	double mn_d = upgrades->get_upgrade("Minimum Damage Up");
	double health = get_random(100 * mn_h, 100 * mx_h);
	double damage = get_random(10 * mn_d, 10 * mx_d);
	int speed = get_random(15 / mn_s, 15 / mx_s);
	if (health < 0 || damage < 0 || speed < 0)
	{
		std::cout << "Matthew Is trash at math";
	}
	piece::stats stat;
	stat.damage = damage;
	stat.speed = speed;
	stat.health = health;

	return stat;
}
void grid::try_spawn_z()
{
	if (z_count < max_z && spawning == false) {
		int x;
		int y;
		int bool1 = get_random(0, 1);  // choses if the zombie will be spawned on x or y axis
		int bool2 = get_random(0, 1);  // choses if the zombie will be top or bottom/left or right
		int position =
			get_random(0, 10);  // choses where on that row/collumn the zombie will be spawned
		if (bool1 == 1) {
			if (bool2 == 1)
				x = -1;
			else
				x = 11;
			y = position;
		} else {
			if (bool2 == 1)
				y = -1;
			else
				y = 11;
			x = position;
		}
		actor::factory<zombie>(this, glm::ivec3(x, y, 2), get_z_stats());
		timer->add_timer(1,
			[this] {
				spawning = false;
				try_spawn_z();
			},
			shared(this));
		spawning = true;
	} else
		spawning = false;
}

int grid::get_z_count() { return z_count; }
void grid::increment_z_count(bool positive)
{
	if (positive)
		z_count++;
	else {
		z_count--;
		try_spawn_z();
	}
}

double grid::get_random(double lower, double higher)
{
	std::uniform_int_distribution<> uniform_double(lower, higher);
	return uniform_double(rand_gen);
}

int grid::get_random(int lower, int higher)
{
	std::uniform_int_distribution<> uniform_int(lower, higher);
	return uniform_int(rand_gen);
}


glm::ivec2 get_location_from_direction (
	glm::ivec2 starting, piece::Directions direction, int Length)
{
	switch (direction) {
	case piece::NORTH: starting.y += Length; break;
	case piece::WEST: starting.x -= Length; break;
	case piece::SOUTH: starting.y -= Length; break;
	case piece::EAST: starting.x += Length; break;
	default: break;
	}
	return starting;
}

