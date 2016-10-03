#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <vector>

#include <ge/subsystem.hpp>

namespace ge
{
struct timer_subsystem;

/// This class represents the metadata for a select timer, you don't have to worry about this class
struct timer_int_data {
	/// Constructor stuff
	timer_int_data(const std::function<void()>& cal,
		std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<float>> expir)
		: callback{cal}, expiration_time{expir}
	{
	}

	/// The callback object
	std::function<void()> callback;

	/// The time at which a timer expires
	std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<float>>
		expiration_time;

	/// If the timer has already been triggered
	bool triggered = false;
};

/// This is similar to a `boost::signals2::connection`, it allows you to manage a timer.
struct timer_handle {
	/// This is called from the timer_manager, you don't have to worry about it.
	timer_handle(timer_manager<void()>* manager,
		const std::shared_ptr<timer_int_data<void()>>& timer)
		: m_manager{manager}, m_data{timer} {};

	/// Gets if the timer has been called
	/// \return If the timer has been called
	bool has_been_called() const { return m_data->triggered; }
	/// Cancels the timer so it won't be called
	void cancel() { m_data->callback = {}; }
	/// Gets how much time is left on the timer since the last tick
	/// \return The float duration of how much time is left
	std::chrono::duration<float> time_left() const
	{
		return std::chrono::duration<float>(m_manager->last_tick - m_data->expiration_time);
	}

private:
	timer_manager* m_manager;
	std::shared_ptr<timer_int_data> m_data;
};

/// This class manages timers
struct timer_subsystem : subsystem {
	
	/// no config
	struct config{};
	bool initialize(config){return true;};
	
	/// Allow timer_handle to modify the manager's internals
	friend timer_handle<void(ArgTypes...)>;

	/// Add a timer to the manager
	/// \param func The function to be called when the time is right
	/// \param duration How long to wait before calling the function
	/// \return The timer_handle used to handle the timer
	timer_handle add_timer(
		std::function<void()> func, std::chrono::duration<float> duration)
	{
		auto dat = std::make_shared<timer_int_data>(func, last_tick + duration);

		m_data.push_back(dat);
		std::push_heap(m_data.begin(), m_data.end(), comp);

		return timer_handle{this, dat};
	}

	/// Advances the timers, calls the ones that need to be
	/// \param duration How much time has happened since the last tick
	/// \param args The arguments to be passed to any timers that have timed out
	void tick(std::chrono::duration<float> duration)
	{
		last_tick += duration;

		while (!m_data.empty() && m_data[0]->expiration_time <= last_tick) {
			if (m_data[0]->callback) {
				m_data[0]->callback(args...);
				m_data[0]->triggered = true;
			}

			// remove the element and retain the heap
			std::pop_heap(m_data.begin(), m_data.end(), comp);
			m_data.pop_back();
		}
	}

private:
	static bool comp(const std::shared_ptr<timer_int_data>& a,
		const std::shared_ptr<timer_int_data>& b)
	{
		return a->expiration_time > b->expiration_time;
	}

	std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<float>> last_tick;

	std::vector<std::shared_ptr<timer_int_data>> m_data;
};



}
