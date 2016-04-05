#pragma once

#include <SDL.h>

#include <boost/optional.hpp> // location is optional

#include <boost/signals2.hpp>

#include <glm/glm.hpp> // for size of window

#include <memory> // for shared_ptr
#include <thread>

namespace ge
{

namespace subsystem
{
// forward declare so we don't have to include
struct graphics;
}

/**
 * The window class. This is part of the graphics subsystem
 */
class window
{
private:
	
	SDL_Window* m_window;
	std::shared_ptr<subsystem::graphics> m_graphics;
	SDL_GLContext m_context;
	glm::vec4 m_background_color;
public:
	
	window(const std::shared_ptr<subsystem::graphics>& graphics, const char* title, glm::uvec2 size, SDL_WindowFlags flags = SDL_WindowFlags(0), boost::optional<glm::uvec2> pos = {});
	
	// can't really copy OpenGL context, so don't allow copying of windows
	window(const window&) = delete;
	
	// move constructor
	window(window&& other)
		:m_window{ other.m_window },
		m_graphics{ std::move(other.m_graphics) }, // move to avoid an atomic increment and decrement
		m_context{ other.m_context },
		signal_quit{ std::move(other.signal_quit) }
	{
		// invalidate `other`
		other.m_window = nullptr;
		other.m_context = nullptr;
	}
	
	// again, can't copy a context, no copy operator
	window& operator=(const window&) = delete;
	
	// move operator
	window& operator=(window&& other)
	{
		this->m_window = other.m_window;
		this->m_graphics = std::move(other.m_graphics);
		this->m_context = other.m_context;
		this->signal_quit = std::move(other.signal_quit);
		
		// invalidate other
		other.m_window = nullptr;
		other.m_context = nullptr;
		
		return *this;
	}
	
	~window();
	
	// checking if it is valid
	operator bool()
	{
		return m_window != nullptr;
	}
	
	void set_background_color(const glm::vec4& new_color)
	{
		m_background_color = new_color;
	}
	glm::vec4 get_background_color()
	{
		return m_background_color;
	}
	
	void start_render_frame();
	void end_render_frame();
	
	SDL_Window* get_sdl_window()
	{
		return m_window;
	}
	
	void handle_events();
	
	
	// signals
	boost::signals2::signal<void()> signal_quit;
	
};

} // namespace ge
