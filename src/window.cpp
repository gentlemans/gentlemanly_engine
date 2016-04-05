#include "gentlemanly_engine/window.hpp"

#include <GL/gl.h>

namespace ge
{
window::window(const std::shared_ptr<subsystem::graphics>& graphics, const char* title, glm::uvec2 size, SDL_WindowFlags flags, boost::optional<glm::uvec2> pos)
{
	// initalize the window
	m_window = SDL_CreateWindow(
		title, 
		pos ? pos.get().x : SDL_WINDOWPOS_UNDEFINED,
		pos ? pos.get().y : SDL_WINDOWPOS_UNDEFINED,
		size.x,
		size.y,
		SDL_WINDOW_OPENGL | flags
	);
	
	using namespace std::string_literals;
	if(!m_window) throw std::runtime_error("Error initalizing SDL window"s + SDL_GetError());
	
	// create the context
	m_context = SDL_GL_CreateContext(m_window);
	
	glEnable(GL_DEPTH_TEST);
	
	set_background_color({.2f, .2f, .2f, 1.f});
}

window::~window()
{
	
	if(m_context) SDL_GL_DeleteContext(m_context);
	
	if(m_window) SDL_DestroyWindow(m_window);
}

void window::start_render_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);
}

void window::end_render_frame()
{
	SDL_GL_SwapWindow(m_window);
}

void window::handle_events()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			signal_quit(); break;
		}
	}
}




} // namespace ge
