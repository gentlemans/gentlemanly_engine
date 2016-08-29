#ifndef GE_SDL_SUBSYSTEM_HPP
#define GE_SDL_SUBSYSTEM_HPP

#pragma once

#include "ge/concept/subsystem.hpp"
#include "ge/input_event.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <memory>
#include <vector>

struct SDL_Window;

namespace ge
{
struct sdl_subsystem
{
	struct config {
		std::string title;
		boost::optional<glm::uvec2> location;
		glm::uvec2 size;
		bool fullscreen = false;
		bool decorated = false;
	};

	bool initialize(const config& config);
	bool update();
	bool shutdown();

	glm::uvec2 get_size() const;
	void set_size(glm::uvec2 new_size);
	
	void set_background_color(const glm::vec4& newColor);
	glm::vec3 get_background_color() const;
	
	std::vector<input_event> get_input_events();
	
private:
	void* m_context; // turns out SDL_GLContext is literally just void*
	SDL_Window* m_window;
};

}  // namespace ge
BOOST_CONCEPT_ASSERT((ge::concept::Subsystem<ge::sdl_subsystem>));

#endif // GE_SDL_SUBSYSTEM_HPP
