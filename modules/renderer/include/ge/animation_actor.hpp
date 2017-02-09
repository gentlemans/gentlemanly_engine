#ifndef GE_ANIMATION_ACTOR_HPP
#define GE_ANIMATION_ACTOR_HPP

#pragma once

#include "ge/mesh_actor.hpp"
#include "ge/mesh_settings_asset.hpp"
#include "ge/runtime.hpp"
#include "ge/tickable.hpp"

namespace ge
{
class animation_actor : public actor
{
public:
	mesh_actor* m_mesh;
	bool m_loops;

	void initialize(const mesh_settings& mes, float fps, bool loops = true)
	{
		m_mesh = factory<mesh_actor>(this, mes).get();
		m_frames_per_second = fps;
		m_loops = loops;
		m_time_until_next_frame =
			std::chrono::duration<float>(std::chrono::seconds(1)) / m_frames_per_second;

		add_interface<animation_actor, tickable>();
	}
	// Just forward to the other one
	void initialize(const char* asset_path, float fps, bool loops = true)
	{
		initialize(*m_runtime->m_asset_manager.get_asset<mesh_settings_asset>(asset_path), fps, loops);
	}

	void tick(std::chrono::duration<float> delta)
	{
		const std::chrono::duration<float> time_per_frame =
			std::chrono::duration<float>(std::chrono::seconds(1)) / m_frames_per_second;

		if (delta >= m_time_until_next_frame) {
			++current_frame;
			delta -= m_time_until_next_frame;
			m_time_until_next_frame = time_per_frame;
		}

		current_frame += delta / time_per_frame;
		m_time_until_next_frame -= delta;

		auto num_frames = *m_mesh->m_mesh_settings.m_material.get_parameter<int>("dimx") *
							*m_mesh->m_mesh_settings.m_material.get_parameter<int>("dimy");
		if (m_loops) {
			current_frame %= num_frames;
		} else {
			
			
			
			
			
			
			
			
			
			
			current_frame = std::min(num_frames - 1, current_frame);
		}
		
		m_mesh->m_mesh_settings.m_material.set_parameter("current_frame", current_frame);
	}

	float m_frames_per_second;

	std::chrono::duration<float> m_time_until_next_frame;

	int current_frame = 0;
};

}  // ge

#endif  // GE_ANIMATION_ACTOR_HPP
