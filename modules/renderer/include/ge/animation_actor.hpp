#ifndef GE_ANIMATION_ACTOR_HPP
#define GE_ANIMATION_ACTOR_HPP

#pragma once

#include "ge/mesh_actor.hpp"
#include "ge/tickable.hpp"
#include "ge/mesh_settings_asset.hpp"
#include "ge/runtime.hpp"

namespace ge {

    class animation_actor : public mesh_actor {
    public:
        void initialize(const mesh_settings& mes, float fps) {

            mesh_actor::initialize(mes);
            m_frames_per_second = fps;

            add_interface<animation_actor, tickable>();

        }
        // Just forward to the other one
        void initialize(const char* asset_path, float fps) {
            initialize(m_runtime->m_asset_manager.get_asset<mesh_settings_asset>(asset_path), fps);
        }

        void tick(std::chrono::duration<float> delta) {
            while(delta > m_time_until_next_frame) {
                ++current_frame;
                delta -= m_time_until_next_frame;
                const std::chrono::duration<float> time_per_frame = std::chrono::duration<float>(std::chrono::seconds(1)) / m_frames_per_second;
                m_time_until_next_frame = time_per_frame;
            }
            m_mesh_settings.m_material.property_values["current_frame"] = current_frame;

        }

        float m_frames_per_second;

        std::chrono::duration<float> m_time_until_next_frame = {};

        int current_frame = 0;
	
};

} // ge

#endif // GE_ANIMATION_ACTOR_HPP
