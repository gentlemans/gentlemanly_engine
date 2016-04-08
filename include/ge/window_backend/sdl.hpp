#pragma once

#include "ge/concept/window_backend.hpp"

#include "ge/window_backend/sdl_window.hpp"
#include "ge/window_backend/sdl_viewport.hpp"

#include "ge/application.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <SDL.h>

#include <memory>

namespace ge {

namespace window_backend {

class sdl
{
public:
	application<sdl>& app;
	
	sdl(application<sdl>& app_, int&, char**)
		:app(app_)
	{
		SDL_Init(SDL_INIT_VIDEO);
	}
	
	using window = sdl_window;
	using viewport = sdl_viewport;
	
	std::unique_ptr<window> create_window(const char* title, boost::optional<glm::uvec2> loc, glm::uvec2 size, bool fullscreen, bool decorated)
	{
		return std::make_unique<window>(*this, title, loc, size, fullscreen, decorated);
	}
	
};
BOOST_CONCEPT_ASSERT((ge::concept::WindowBackend<sdl>));

} // namespace window_backend
} // namespace qt
