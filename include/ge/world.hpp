#pragma once

#include <boost/signals2.hpp>

#include <deque>
#include <type_traits>
#include <iterator>

#include <Box2D/Box2D.h>

namespace ge
{
class actor;

class world
{
	friend actor;
	friend class physics_controller;

	// use a deque so we don't get iterator invaidation during foreach
	std::deque<size_t> empty_slots;
	std::deque<actor*> actors;

	b2World m_b2_world;

public:
	world() : m_b2_world{{0, 0}} {}
	~world() = default;

	boost::signals2::signal<void(float delta_time)> signal_update;

	template <typename callback>
	void for_each_actor(callback&& func_to_call)
	{
		auto actor_it = actors.begin();
		auto empty_slots_it = empty_slots.begin();

		while (actor_it != actors.end())
		{
			if (*empty_slots_it == std::distance(actor_it, actors.begin()))
			{
				++empty_slots_it;
				continue;
			}

			std::forward<callback>(func_to_call)(*actor_it);

			++actor_it;
		}
	}

	void set_gravity(glm::vec2 gravity) { m_b2_world.SetGravity({gravity.x, gravity.y}); }
	glm::vec2 get_gravity() const
	{
		auto tmp = m_b2_world.GetGravity();
		return {tmp.x, tmp.y};
	}
};
}
