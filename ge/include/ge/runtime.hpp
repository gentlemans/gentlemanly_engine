#ifndef GE_RUNTIME_HPP
#define GE_RUNTIME_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/hash_typeindex.hpp"
#include "ge/subsystem.hpp"

#include <chrono>
#include <memory>
#include <unordered_map>

#include <boost/type_index.hpp>

#include <spdlog/spdlog.h>

namespace ge
{
class actor;
/// The subsystem manager for the engine. This is the highest up primative the engine defines
struct runtime {
	/// Defualt constructor
	runtime() : m_asset_manager{*this} { m_log = spdlog::stdout_logger_mt("ge_log"); }
	/// Destructor
	~runtime()
	{
		// call shutdown on the subsystems
		bool overall_success = true;
		for (auto iter = m_add_order.rbegin(); iter < m_add_order.rend(); ++iter) {
			bool this_success = (*iter)->shutdown();
			if (!overall_success) overall_success = this_success;
		}

		// see if it was successful
		// TODO: logging
	}

	/// Adds a new subsystem. Subsystems must derrive from \c ge::subsystem and also must implemet a
	/// function like: bool initialize(Subsystem::config c)
	/// \param config The config object to send when initializing the submodule.
	template <typename Subsystem>
	Subsystem& add_subsystem(const typename Subsystem::config& config)
	{
		static_assert(std::is_base_of<subsystem, Subsystem>::value,
			"Cannot add a subsystem of a non-subsystem type");

		using boost::typeindex::type_id;

		// see if there is already one
		auto existing_iter = m_subsystems.find(type_id<Subsystem>());
		if (existing_iter != m_subsystems.end()) {
			// we aren't interseted in adding another one
			return *static_cast<Subsystem*>(existing_iter->second.get());
		}

		auto new_subsystem = std::make_unique<Subsystem>();

		new_subsystem->m_runtime = this;
		bool success = new_subsystem->initialize(config);

		if (success) {
			m_log->info(
				"Subsystem \"" + type_id<Subsystem>().pretty_name() + "\" sucessfully loaded.");
		} else {
			m_log->error("Subsystem \"" + type_id<Subsystem>().pretty_name() +
						 "\" failed to load. Program execution will continue, but ");
		}

		// add it!
		auto inserted_iter =
			m_subsystems.insert(std::make_pair(type_id<Subsystem>(), std::move(new_subsystem)))
				.first;
		m_add_order.push_back(inserted_iter->second.get());

		return *static_cast<Subsystem*>(inserted_iter->second.get());
	}

	/// Fetches a already existing submodule
	/// \return The submodule, or nullptr if it doens't exist
	template <typename Subsystem>
	Subsystem* get_subsystem() noexcept
	{
		using boost::typeindex::type_id;

		auto iter = m_subsystems.find(type_id<Subsystem>());
		if (iter != m_subsystems.end()) {
			return static_cast<Subsystem*>(iter->second.get());
		}

		return nullptr;
	}

	/// Render the next frame
	bool tick()
	{
		// first run
		if (first_tick == std::chrono::system_clock::time_point{}) {
			first_tick = last_tick = std::chrono::system_clock::now();
		}

		auto current_time = std::chrono::system_clock::now();

		auto tick_duration = std::chrono::duration<float>(current_time - last_tick);

		last_tick = current_time;

		bool keep_running = true;
		for (auto& subsystem : m_subsystems) {
			auto result = subsystem.second->update(tick_duration);
			if (keep_running) keep_running = result;
		}

		return keep_running;
	}
	/// Set the root actor that is to be used by subsystems
	/// \param new_root The new root actor
	inline void set_root_actor(actor* new_root);

	/// Gets the root actor, can be nullptr
	/// \return The root actor
	actor* get_root_actor() const { return m_root_actor.get(); }
	/// Get the total elased time of the runtiime since the first tick
	std::chrono::duration<float> get_elapsed_time() const { return first_tick - last_tick; }
	/// The asset manager
	asset_manager m_asset_manager;

	std::shared_ptr<spdlog::logger> m_log;

private:
	std::shared_ptr<actor> m_root_actor;

	std::unordered_map<boost::typeindex::type_index, std::unique_ptr<subsystem>> m_subsystems;
	std::vector<subsystem*> m_add_order;

	std::chrono::system_clock::time_point first_tick, last_tick;
};
}
#include "ge/actor.hpp"

void ge::runtime::set_root_actor(actor* new_root) { m_root_actor = ge::actor::shared(new_root); }
#endif  // GE_RUNTIME_HPP
