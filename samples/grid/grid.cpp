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

	auto timer = m_runtime->get_subsystem<ge::timer_subsystem>();

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

	timer->add_timer(func, std::chrono::duration<float>(std::chrono::seconds(1)) / tps, true);
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
