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
