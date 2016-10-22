#include "grid.hpp"

#include "base.hpp"

#include <ge/runtime.hpp>
#include <ge/timer_subsystem.hpp>

#include "gridtick_interface.hpp"

void grid::initialize(glm::uvec3 size, float tps)
{
	set_relative_location(glm::vec2(-float(size.x) / 2.f, -float(size.y) / 2.f));

	m_size = size;

	ge::actor::factory<base>(this, glm::uvec3{size.x / 2, size.y / 2, 2}).get();

	auto timer = m_runtime->get_subsystem<ge::timer_subsystem>();

	auto func = [this] {
		m_runtime->get_root_actor()->propagate_to_children([](actor& act) {
			auto storage = act.get_interface_storage<gridtick_interface>();
			if (storage) {
				storage->callback();
			}
		});
	};

	timer->add_timer(func, std::chrono::duration<float>(std::chrono::seconds(1)) / tps, true);
}
std::vector<piece*> grid::get_actor_from_coord(glm::uvec3 loc)
	{
		assert(loc.x < m_size.x);
		assert(loc.y < m_size.y);
		assert(loc.z < 3);

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
