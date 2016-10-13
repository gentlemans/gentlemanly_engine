#include "grid.hpp"

#include "base.hpp"

#include <ge/runtime.hpp>
#include <ge/timer_subsystem.hpp>

#include "gridtick_interface.hpp"

void grid::initialize(glm::uvec3 size, float tps)
{
	set_relative_location(glm::vec2(-float(size.x) / 2.f, -float(size.y) / 2.f));

	m_size = size;

	towers.resize(size.x * size.y * size.z);

	getActorFromCoord({size.x / 2, size.y / 2, 2}) =
		ge::actor::factory<base>(this, glm::uvec3{size.x / 2, size.y / 2, 2}).get();

    auto timer = m_runtime->get_subsystem<ge::timer_subsystem>();

    auto func = [this]{
        m_runtime->get_root_actor()->propagate_to_children([](actor& act){
            auto storage = act.get_interface_storage<gridtick_interface>();
            if(storage) {
                storage->callback();
            }
        });
    };

    timer->add_timer(func, std::chrono::duration<float>(std::chrono::seconds(1)) / tps, true);

}
