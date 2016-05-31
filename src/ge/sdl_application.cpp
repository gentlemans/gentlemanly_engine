#include "ge/gl.hpp"
#include "ge/sdl_application.hpp"

#include "SDL.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <chrono>


namespace ge
{
sdl_application::sdl_application(int&, char**) { SDL_Init(SDL_INIT_VIDEO); }
void update_c_function(void* void_app)
{
	auto app = (sdl_application*)void_app;

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::chrono::duration<float> diff = now - last_tick;

	app->signal_update(diff.count());

	last_tick = now;
}

void sdl_application::execute(window& win)
{
	signal_init();

	SDL_GL_SetSwapInterval(1);

#ifdef EMSCRIPTEN

	emscripten_set_main_loop_arg(update_c_function, this, -1, 1);

#else

	SDL_GL_SetSwapInterval(0);

	while (running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_c_function(this);
		SDL_GL_SwapWindow(win.m_window);
	}

#endif

	signal_quit();
}

}  // namespace ge
