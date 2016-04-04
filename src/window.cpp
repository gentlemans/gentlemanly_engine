#include "gentlemanly_engine/window.hpp"


namespace ge
{
	window::window(const char* title, glm::uvec2 size, SDL_WindowFlags flags, boost::optional<glm::uvec2> pos)
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
	}
}
