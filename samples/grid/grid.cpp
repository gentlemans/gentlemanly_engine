#include "grid.hpp"

#include "base.hpp"
#include "zombie.hpp"

#include <ge/runtime.hpp>
#include <ge/timer_subsystem.hpp>

#include "gridtick_interface.hpp"

void grid::initialize(glm::ivec2 size, float tps)
{
    // the 0.5 is because the locations are the centers, so we need to account for that
    set_relative_location(glm::vec2(-float(size.x) / 2.f + 0.5, -float(size.y) / 2.f + 0.5));

	m_size = size;

    auto b = ge::actor::factory<base>(this, glm::ivec3{size.x / 2, size.y / 2, 2});

    auto timersub = m_runtime->get_subsystem<ge::timer_subsystem>();

	auto func = [this] {
		
		auto* interface = m_runtime->get_interface<gridtick_interface>();
		
		assert(interface);
		
		std::vector<std::vector<std::weak_ptr<actor>>::iterator> toDel;
		
		for(auto actiter = interface->attached.begin(); actiter != interface->attached.end(); ++actiter) {
			if(actiter->expired()) {
				toDel.push_back(actiter);
				continue;
			}
			actiter->lock()->get_interface_storage<gridtick_interface>()->callback();
		}
		
		for(auto del : toDel) {
			interface->attached.erase(del);
		}

		// actor::factory<zombie>(this, glm::ivec3{get_random(0, 10), get_random(0, 10), 2});
	};

    timersub->add_timer(func, std::chrono::duration<float>(std::chrono::seconds(1)) / tps, true);

    timer = ge::actor::factory<ticktimer>(this).get();

}
std::vector<piece*> grid::get_actors_from_coord(glm::ivec3 loc)
{
	std::vector<piece*> ret;

	for (auto& child : m_children) {
		piece* p = dynamic_cast<piece*>(child.get());
		if (!p) continue;

		if (p->get_relative_location() == glm::vec2{loc.x, loc.y} && p->m_level == loc.z) {
			ret.push_back(p);
		}
	}

	return ret;
}
void grid::try_spawn_z()
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
		actor::factory<zombiespawner>(this, glm::ivec3(x, y, 2));
		increment_z_count(1);
		timer->add_timer(1, [this] {
			spawning = false;
			try_spawn_z();
		}, shared(this));
		spawning = true;
	}
	else
		spawning = false;
}
