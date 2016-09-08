#ifndef GE_SDL_SUBSYSTEM_HPP
#define GE_SDL_SUBSYSTEM_HPP

#pragma once

#include "ge/input_event.hpp"
#include "ge/subsystem.hpp"
#include "ge/camera_actor.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <memory>
#include <vector>

struct SDL_Window;

namespace ge
{
struct sdl_subsystem : subsystem {
	struct config {
		std::string title;
		boost::optional<glm::uvec2> location;
		glm::uvec2 size;
		bool fullscreen = false;
		bool decorated = true;
	};

	bool initialize(const config& conf);
	virtual bool update(std::chrono::duration<float> delta) override;
	virtual bool shutdown() override;

	glm::uvec2 get_size() const;
	void set_size(glm::uvec2 new_size);

	std::string get_title() const;
	void set_title(const std::string& newTitle);

	void set_background_color(const glm::vec3& newColor) noexcept {
		m_background_color = newColor;
	}
	glm::vec3 get_background_color() const noexcept { return m_background_color; }
	
	camera_actor* get_camera() const noexcept { return m_camera.get(); }
	void set_camera(camera_actor* cam) noexcept { m_camera = actor::shared(cam); }
	
	actor* get_root_actor() const noexcept { return m_root_actor.get(); }
	void set_root_actor(actor* new_root) noexcept { m_root_actor = actor::shared(new_root); }


	std::vector<input_event> get_input_events();

private:
	void* m_context = nullptr;  // turns out SDL_GLContext is literally just void*
	SDL_Window* m_window = nullptr;
	glm::vec3 m_background_color;
	std::vector<input_event> unprocessed_events;
	std::shared_ptr<camera_actor> m_camera;
	std::shared_ptr<actor> m_root_actor;
};

}  // namespace ge

#endif  // GE_SDL_SUBSYSTEM_HPP
