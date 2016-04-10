#include "ge/window_backend/sdl_window.hpp"
#include "ge/window_backend/sdl.hpp"

#include <GL/gl.h>

#include <SDL.h>

namespace ge {
namespace window_backend {

sdl_window::sdl_window(sdl& sdl_inst_, const char* title, boost::optional<glm::uvec2> loc, glm::uvec2 size, bool fullscreen, bool decorated)
	:sdl_inst(&sdl_inst_)
{
	int flags = SDL_WINDOW_OPENGL |
		(fullscreen ? SDL_WINDOW_FULLSCREEN : 0) |
		(decorated ? 0 : SDL_WINDOW_BORDERLESS);
	
	// initalize the window
	m_window = SDL_CreateWindow(
		title, 
		loc ? loc.get().x : SDL_WINDOWPOS_UNDEFINED,
		loc ? loc.get().y : SDL_WINDOWPOS_UNDEFINED,
		size.x,
		size.y,
		flags
	);
	
	using namespace std::string_literals;
	if(!m_window) throw std::runtime_error("Error initalizing SDL window"s + SDL_GetError());
	
	// create the context
	m_context = SDL_GL_CreateContext(m_window);
	
	glEnable(GL_DEPTH_TEST);
	
	sdl_inst->app.update.connect([this] {
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				sig_quit();
			}
		}
		glFlush();
		SDL_GL_SwapWindow(m_window);
	});
}

sdl_window::~sdl_window()
{
	
	if(m_context) SDL_GL_DeleteContext(m_context);
	if(m_window) SDL_DestroyWindow(m_window);
}

void sdl_window::set_title(const char* new_title)
{
	SDL_SetWindowTitle(m_window, new_title);
}

std::string sdl_window::get_title() const
{
	return SDL_GetWindowTitle(m_window);
}

} // namespace window_backend
} // namespace ge
