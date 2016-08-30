#ifndef GE_SDL_SUBSYSTEM_HPP
#define GE_SDL_SUBSYSTEM_HPP

#pragma once

#include "ge/subsystem.hpp"
#include "ge/input_event.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <memory>
#include <vector>

struct SDL_Window;

namespace ge
{
struct sdl_subsystem : subsystem
{
	
	struct config {
		std::string title;
		boost::optional<glm::uvec2> location;
		glm::uvec2 size;
		bool fullscreen = false;
		bool decorated = true;
	};
	
	


	bool initialize(const config& conf);
	virtual bool update() override;
	virtual bool shutdown() override;

	glm::uvec2 get_size() const;
	void set_size(glm::uvec2 new_size);
	
	std::string get_title() const;
	void set_title(const std::string& newTitle);
	
	void set_background_color(const glm::vec3& newColor);
	glm::vec3 get_background_color() const;
	
	std::vector<input_event> get_input_events();
	
private:
	void* m_context = nullptr; // turns out SDL_GLContext is literally just void*
	SDL_Window* m_window = nullptr;
	bool shouldstayrunning = true;
	glm::vec3 backgroundcolor;
	
	
};

}  // namespace ge

#endif // GE_SDL_SUBSYSTEM_HPP
