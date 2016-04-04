#pragma once

#include <SDL.h>

#include <string>

// for location
#include <boost/optional.hpp>

// for size
#include <glm/glm.hpp>

namespace ge
{

class window
{
	SDL_Window* SDL_window;
public:
	window(const char* title, glm::uvec2 size, SDL_WindowFlags flags = SDL_WindowFlags(0), boost::optional<glm::uvec2> pos = {});
	
	// can't really copy OpenGL context, so don't allow copying of windows
	window(const window&) = delete;
	
	// move constructor
	window(window&& other)
	{
		this->SDL_window = other.SDL_window;
		// invalidate `other`
		other.SDL_window = nullptr;
	}
	
	
};

} // namespace ge
