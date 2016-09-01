#ifndef GE_RUNTIME_HPP
#define GE_RUNTIME_HPP

#pragma once

#include "ge/hash_typeindex.hpp"
#include "ge/subsystem.hpp"

#include <chrono>
#include <memory>
#include <unordered_map>

#include <boost/type_index.hpp>

namespace ge
{
struct runtime {
	template <typename Subsystem>
	void add_subsystem(const typename Subsystem::config& config)
	{
		static_assert(std::is_base_of<subsystem, Subsystem>::value,
			"Cannot add a subsystem of a non-subsystem type");

		using boost::typeindex::type_id;

		// see if there is already one
		if (m_subsystems.find(type_id<Subsystem>()) != m_subsystems.end()) {
			// we aren't interseted in adding another one
			return;
		}

		auto new_subsystem = std::make_unique<Subsystem>();

		new_subsystem->m_runtime = this;
		new_subsystem->initialize(config);

		// add it!
		m_subsystems[type_id<Subsystem>()] = std::move(new_subsystem);
	}

	template <typename Subsystem>
	Subsystem* get_subsystem()
	{
		using boost::typeindex::type_id;

		if (auto iter = m_subsystems.find(type_id<Subsystem>()) != m_subsystems.end()) {
			return static_cast<Subsystem>(iter.second.get());
		}

		return nullptr;
	}

	void tick()
	{
		// first run
		if (last_tick == std::chrono::system_clock::time_point{}) {
			last_tick = std::chrono::system_clock::now();
		}

		auto current_time = std::chrono::system_clock::now();

		auto tick_duration = std::chrono::duration<float>(current_time - last_tick);
	}

private:
	std::unordered_map<boost::typeindex::type_index, std::unique_ptr<subsystem>> m_subsystems;

	std::chrono::system_clock::time_point last_tick;
};
}

#endif  // GE_RUNTIME_HPP
