#ifndef GE_INPUT_CONSUMER_HPP
#define GE_INPUT_CONSUMER_HPP

#pragma once

#include "ge/input_event.hpp"
#include "ge/sdl_subsystem.hpp"

#include <deque>
#include <functional>

namespace ge
{
/// The base class for input consumers to make checking for input_consumer classes easier
struct input_consumer_base {
};

/// The manager for input_consumers. It stores the active one and forwards all events to it.
struct input_consumer_manager {
	/// The signature of a function that consumes input
	using consumer_func = void(input_event event, input_consumer_base* ptr);

	/// The stack of consumers
	static std::deque<std::pair<consumer_func*, input_consumer_base*>> consumers;

	/// The index in \c consumers of the current consumer
	static size_t active_consumer;

	/// This is called when events need to be processed.
	/// \param subsystem The subsystem to process events from
	static void process_events(sdl_subsystem& subsystem)
	{
		if (consumers.size() > active_consumer) {
			auto events = subsystem.get_input_events();

			for (auto ev : events) {
				consumers[active_consumer].first(ev, consumers[active_consumer].second);
			}
		}
	}
};

/// The CRTP class to build an input consumer.
template <typename Derived>
struct input_consumer : input_consumer_base {
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
	/// This function is to be ran from the base class and it forwards all input to this class.
	void steal_input() { input_consumer_manager::active_consumer = consumer_id; }
private:
	size_t consumer_id;
};
}

#endif  // GE_INPUT_CONSUMER_HPP
