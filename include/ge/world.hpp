#pragma once

#include <boost/signals2.hpp>

#include <deque>
#include <type_traits>
#include <iterator>

namespace ge
{
class actor;

class world
{
	friend actor;

	// use a deque so we don't get iterator invaidation during foreach
	std::deque<size_t> empty_slots;
	std::deque<actor*> actors;

public:
	boost::signals2::signal<void(float delta_time)> update;

	template<typename callback>
	void for_each_actor(callback&& func_to_call)
	{
		auto actor_it = actors.begin();
		auto empty_slots_it = empty_slots.begin();
		
		while(actor_it != actors.end())
		{
			if(*empty_slots_it == std::distance(actor_it, actors.begin()))
			{
				++empty_slots_it;
				continue;
			}
			
			std::forward<callback>(func_to_call)(*actor_it);
			
			++actor_it;
		}
	}
	
};
}
