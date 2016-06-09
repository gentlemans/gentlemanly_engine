#pragma once

#include "ge/concept/application.hpp"

#include "ge/sdl_viewport.hpp"
#include "ge/sdl_window.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <boost/signals2.hpp>

#include <memory>

namespace ge
{
class sdl_application
{
	friend class sdl_window;
	friend class sdl_viewport;

	bool running = true;
	

public:
	sdl_application(int&, char**);

	using window = sdl_window;
	using viewport = sdl_viewport;

	std::unique_ptr<window> make_window(const char* title, boost::optional<glm::uvec2> loc,
		glm::uvec2 size, bool fullscreen, bool decorated)
	{
		return std::make_unique<window>(*this, title, loc, size, fullscreen, decorated);
	}

	std::unique_ptr<viewport> make_viewport(window& window)
	{
		return std::make_unique<viewport>(window);
	}

	void request_quit() { running = false; }
	// signals
	boost::signals2::signal<void(float)> signal_update;
	boost::signals2::signal<void()> signal_init;
	boost::signals2::signal<void()> signal_quit;

	void execute(window& win);
	
	float get_elapsed_time() const {
		return elapsed_time;
	}
	
	float elapsed_time = 0.f;
	
};
BOOST_CONCEPT_ASSERT((ge::concept::Application<sdl_application>));

}  // namespace qt
