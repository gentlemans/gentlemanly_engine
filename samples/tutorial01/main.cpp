#include <ge/input_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/actor_ticker_subsystem.hpp>

int main()
{
	ge::runtime r;

	r.add_subsystem<ge::actor_ticker_subsystem>({});
	r.add_subsystem<ge::input_subsystem>({});

	r.add_subsystem<ge::sdl_subsystem>({
		"hello ge!",  // title of the window
		{},  // location on the screen, {} for OS defined (it's a boost::optional<glm::uvec2>)
		{720, 1280},  // the size of the window
		false,		  // fullscreen or not
		true		  // if the window should be decorated (border etc).
	});

	while (r.tick())
		;
}
