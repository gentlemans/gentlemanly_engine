#pragma once

// SDL2
#include <SDL.h>

// for location
#include <boost/optional.hpp>

// for size
#include <glm/glm.hpp>

// forward declare so we don't have to include SDL

namespace ge
{

/**
 * The window class. This is part of the graphics subsystem
 */
class window
{
	
	SDL_Window* m_window;
public:
	window(const char* title, glm::uvec2 size, SDL_WindowFlags flags = SDL_WindowFlags(0), boost::optional<glm::uvec2> pos = {});
	
	// can't really copy OpenGL context, so don't allow copying of windows
	window(const window&) = delete;
	
	// move constructor
	window(window&& other)
		:m_window{ other.m_window }
	{
		// invalidate `other`
		other.m_window = nullptr;
	}
	
	// again, can't copy a context, no copy operator
	window& operator=(const window&) = delete;
	
	// move operator
	window& operator=(window&& other)
	{
		this->m_window = other.m_window;
		
		// invalidate other
		other.m_window = nullptr;
		
		return *this;
	}
	
	// checking if it is valid
	operator bool()
	{
		return m_window != nullptr;
	}
	
	
	
};

} // namespace ge
