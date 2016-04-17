#include "ge/sdl_application.hpp"

#include "SDL.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <chrono>

namespace ge
{
sdl_application::sdl_application(int&, char**) { SDL_Init(SDL_INIT_VIDEO); }

void update_c_function(sdl_application* app) { 
	
	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();
	
	std::chrono::duration<float> diff =  now - last_tick;
	
	app->signal_update(std::chrono::duration_cast<std::chrono::seconds>(diff).count());
	
	last_tick = now;
	
}

void sdl_application::execute()
{
	signal_init();

	SDL_GL_SetSwapInterval(1);


#ifdef EMSCRIPTEN

	emscripten_set_main_loop(run, -1, 1);

#else
	
	while(running) {
		update_c_function(this);
	}
	
#endif
}

}  // namespace ge
