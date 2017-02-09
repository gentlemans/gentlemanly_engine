#ifndef TICKTIMER_SUBSYSTEM_HPP
#define TICKTIMER_SUBSYSTEM_HPP

#include <ge/actor.hpp>
#include <ge/subsystem.hpp>

#include "gridtick_interface.hpp"

#include <boost/signals2.hpp>

struct ticktimer : public ge::actor {
	void initialize() { add_interface<ticktimer, gridtick_interface>(); }
	std::deque<boost::signals2::signal<void()>> callbacks;

	void tick_grid()
	{
		// run the callbakcs
		if (!callbacks.empty()) {
			callbacks[0]();

			callbacks.pop_front();
		}
	}

	boost::signals2::connection add_timer(
		int nTicks, std::function<void()> call, const std::weak_ptr<void>& track)
	{
		if (callbacks.size() <= nTicks) {
			callbacks.resize(nTicks + 1);
		}
		return callbacks[nTicks].connect(
			boost::signals2::signal<void()>::slot_type(call).track_foreign(track));
	}

	boost::signals2::connection add_timer(int nTicks, std::function<void()> call)
	{
		if (callbacks.size() <= nTicks) {
			callbacks.resize(nTicks + 1);
		}

		return callbacks[nTicks].connect(call);
	}
};

#endif  // TICKTIMER_SUBSYSTEM_HPP
