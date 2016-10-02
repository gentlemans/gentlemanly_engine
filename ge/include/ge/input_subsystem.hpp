#ifndef GE_INPUT_SUBSYSTEM_HPP
#define GE_INPUT_SUBSYSTEM_HPP

#pragma once

#include "ge/input_event.hpp"
#include "ge/runtime.hpp"
#include "ge/subsystem.hpp"

#include <functional>
#include <vector>

namespace ge
{
/// The base class for input consumers to make checking for input_consumer classes easier
struct input_consumer_base {
};

/// The manager for input_consumers. It stores the active one and forwards all events to it.
struct input_subsystem : subsystem {
	/// The signature of a function that consumes input
	using consumer_func = void(input_event event, input_consumer_base* ptr);

	/// The index in \c consumers of the current consumer
	size_t active_consumer;

	/// No config needed
	struct config {
	};

	/// Init function, nothing to do
	bool initialize(config) { return true; }
	/// Adds an event to the input_subsystem, to be passed during the update function.
	/// \param ev The event to pass
	void add_event(input_event ev) { buffered_events.push_back(ev); }
	/// This is called when events need to be processed.
	virtual bool update(std::chrono::duration<float>) override
	{
		// if the active consumer doesn't exist, then return early
		if (consumers.size() <= active_consumer) return true;
		size_t before_size = buffered_events.size();
		if (before_size == 0) return true;  // No events

		for (auto& ev : buffered_events) {
			consumers[active_consumer].first(ev, consumers[active_consumer].second);
		}
		// empty the buffer--conserve elements that were added during the callbacks.
		buffered_events.erase(buffered_events.begin(), buffered_events.begin() + before_size);

		return true;
	}

	/// The list of consumers
	std::vector<std::pair<consumer_func*, input_consumer_base*>> consumers;

private:
	std::deque<input_event> buffered_events;
};

/// The CRTP class to build an input consumer.
template <typename Derived>
struct input_consumer : input_consumer_base {
	/// Constuctor
	/// \param run The runtime to add it to
	input_consumer(runtime* run)
	{
		input_sub = run->get_subsystem<input_subsystem>();

		// the input subsystem must be loaded before initialzing an input_consumer
		if (!input_sub) std::terminate();

		input_sub->consumers.push_back({[](input_event event, input_consumer_base* ptr) {
											Derived* der = static_cast<Derived*>(ptr);

											der->handle_input(event);
										},
			this});

		consumer_id = input_sub->consumers.size() - 1;
	}

protected:
	/// This function is to be ran from the base class and it forwards all input to this class.
	void steal_input() { input_sub->active_consumer = consumer_id; }
private:
	size_t consumer_id;
	input_subsystem* input_sub;
};
}

#endif  // GE_INPUT_SUBSYSTEM_HPP
