#include "ge/window_backend/sdl.hpp"

#include "SDL.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

namespace ge
{
namespace window_backend
{
sdl::sdl(application<sdl>& app_, int&, char**) : app(app_) { SDL_Init(SDL_INIT_VIDEO); }
sdl* inst;

void run() { inst->app.update(); }
void sdl::execute()
{
	app.init();

	SDL_GL_SetSwapInterval(1);

	inst = this;

#ifdef EMSCRIPTEN

	emscripten_set_main_loop(run, -1, 1);

#else

	while (running)
	{
		app.update();
	}
#endif
}

}  // namespace ge
}  // namespace window_backend
