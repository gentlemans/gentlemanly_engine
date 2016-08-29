#include "ge/sdl_subsystem.hpp"
#include "ge/gl.hpp"

#include "SDL.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <chrono>

namespace ge
{
bool sdl_subsystem::initialize(const sdl_subsystem::config& config) { 
	SDL_Init(SDL_INIT_VIDEO);
	
	// create the window
	int flags = SDL_WINDOW_OPENGL | (config.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) |
				(config.decorated ? 0 : SDL_WINDOW_BORDERLESS);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glm::uvec2 loc = config.location ? config.location.get() : glm::uvec2{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED};
	
	// initalize the window
	m_window = SDL_CreateWindow(config.title.c_str(), loc.x, loc.y, config.size.x, config.size.y, flags);

	using namespace std::string_literals;
	if (!m_window) throw std::runtime_error("Error initalizing SDL window"s + SDL_GetError());

	// create the context
	m_context = SDL_GL_CreateContext(m_window);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable alpha testing
	glAlphaFunc ( GL_GREATER, 0.1 ) ;
	glEnable ( GL_ALPHA_TEST ) ;
	
#	ifdef EMSCRIPTEN

	emscripten_set_main_loop_arg(update_c_function, this, -1, 1);

#	endif
}


// we need the C function because emscripten needs a C update function
// TODO: this probably needs to be in a wrapper around runtime
void update_c_function(void* void_subsystem)
{
	auto subsystem = (sdl_subsystem*)void_subsystem;

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::chrono::duration<float> diff = now - last_tick;

	//app->signal_update(diff.count());
	//app->elapsed_time += diff.count();

	last_tick = now;
}

bool sdl_subsystem::update()
{

#	ifndef EMSCRIPTEN

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	update_c_function(this);
	SDL_GL_SwapWindow(m_window);

#	endif

}

}  // namespace ge
