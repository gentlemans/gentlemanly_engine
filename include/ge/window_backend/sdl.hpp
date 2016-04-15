#pragma once

#include "ge/concept/window_backend.hpp"

#include "ge/window_backend/sdl_window.hpp"
#include "ge/window_backend/sdl_viewport.hpp"

#include "ge/application.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <memory>

namespace ge
{
namespace window_backend
{
class sdl
{
	friend class sdl_window;

	bool running = true;

public:
	application<sdl>& app;

	sdl(application<sdl>& app_, int&, char**);

	using window = sdl_window;
	using viewport = sdl_viewport;

	std::unique_ptr<window> make_window(const char* title, boost::optional<glm::uvec2> loc,
										glm::uvec2 size, bool fullscreen, bool decorated)
	{
		return std::make_unique<window>(*this, title, loc, size, fullscreen, decorated);
	}

	std::unique_ptr<viewport> make_viewport(window& win)
	{
		return std::make_unique<viewport>(&win);
	}

	void execute();

	void request_exit() { running = false; }
};
BOOST_CONCEPT_ASSERT((ge::concept::WindowBackend<sdl>));

}  // namespace window_backend
}  // namespace qt
