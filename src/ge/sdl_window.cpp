#include "ge/sdl_window.hpp"
#include "ge/gl.hpp"
#include "ge/sdl_application.hpp"

#include "SDL.h"

namespace ge
{
sdl_window::sdl_window(sdl_application& sdl_inst_, const char* title,
	boost::optional<glm::uvec2> loc, glm::uvec2 size, bool fullscreen, bool decorated)
	: sdl_inst(&sdl_inst_)
{
	int flags = SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) |
				(decorated ? 0 : SDL_WINDOW_BORDERLESS);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// initalize the window
	m_window = SDL_CreateWindow(title, loc ? loc.get().x : SDL_WINDOWPOS_UNDEFINED,
		loc ? loc.get().y : SDL_WINDOWPOS_UNDEFINED, size.x, size.y, flags);

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


}

sdl_window::~sdl_window()
{
	if (m_context) SDL_GL_DeleteContext(m_context);
	if (m_window) SDL_DestroyWindow(m_window);
}

void sdl_window::set_title(const char* new_title) { SDL_SetWindowTitle(m_window, new_title); }
std::string sdl_window::get_title() const { return SDL_GetWindowTitle(m_window); }
void sdl_window::set_size(glm::uvec2 new_size)
{
	SDL_SetWindowSize(m_window, new_size.x, new_size.y);
}

glm::uvec2 sdl_window::get_size() const
{
	glm::ivec2 ret;  // needs to be ivec because SDL_GetWindowSize only accepts ints
	SDL_GetWindowSize(m_window, &ret.x, &ret.y);

	return ret;
}

}  // namespace ge
