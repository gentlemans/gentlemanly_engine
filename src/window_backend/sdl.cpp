#include "ge/window_backend/sdl.hpp"

#include <iostream>

#include <SDL.h>

namespace ge {
namespace window_backend {

sdl::sdl(application<sdl>& app_, int&, char**)
	:app(app_)
{
	SDL_Init(SDL_INIT_VIDEO);
}

void sdl::execute()
{
	while(running)
	{
		app.update();
	}
}


} // namespace ge
} // namespace window_backend
