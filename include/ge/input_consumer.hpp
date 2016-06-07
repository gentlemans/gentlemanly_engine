#pragma once

#include "ge/concept/viewport.hpp"
#include "ge/input_event.hpp"

#include <deque>
#include <functional>

namespace ge
{
struct input_consumer_base
{
};

struct input_consumer_manager
{
	using consumer_func = void(input_event event, input_consumer_base* ptr);

	static std::deque<std::pair<consumer_func*, input_consumer_base*>> consumers;
	static size_t active_consumer;

	template <typename Viewport>
	static void process_events(Viewport& viewport)
	{
		BOOST_CONCEPT_ASSERT((ge::concept::Viewport<Viewport>));

		if (consumers.size() > active_consumer)
		{
			auto events = viewport.get_input_events();

			for (auto ev : events)
			{
				consumers[active_consumer].first(ev, consumers[active_consumer].second);
			}
		}
	}
};

template <typename Derived>
struct input_consumer : input_consumer_base
{
	input_consumer()
	{
		input_consumer_manager::consumers.push_back(
			{[](input_event event, input_consumer_base* ptr) {
				 Derived* der = static_cast<Derived*>(ptr);

				 der->handle_input(event);
			 },
				this});

		consumer_id = input_consumer_manager::consumers.size() - 1;
	}

protected:
	void steal_input() { input_consumer_manager::active_consumer = consumer_id; }
private:
	size_t consumer_id;
};
}
