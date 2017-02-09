#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>
#include <ge/rocket_document_asset.hpp>
#include <ge/rocket_input_consumer.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>

#include <iostream>
#include <memory>

using namespace ge;

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

int main(int argc, char** argv)
{
	try {
		runtime r;
		r.m_asset_manager.add_asset_path("data/");
		r.add_subsystem<input_subsystem>({});
		auto& sdl = r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Example!", {1024, 720}});
		r.add_subsystem<rocket_subsystem>({});

		auto root = actor::root_factory(&r);

		auto camera = actor::factory<camera_actor>(
			root.get(), 10, float(sdl.get_size().x) / float(sdl.get_size().y));

		sdl.set_background_color({.2f, .2f, .2f});
		sdl.set_camera(camera.get());
		r.set_root_actor(root.get());

		auto document =
			r.m_asset_manager.get_asset<rocket_document_asset>("rocket/example.rocketdoc");
		document->Show();

		rocket_input_consumer ic{&r};
		ic.steal_input();
#ifdef EMSCRIPTEN
		emscripten_set_main_loop_arg(
			[](void* run_ptr) {
				runtime* runt = (runtime*)run_ptr;

				runt->tick();
			},
			&r, 0, true);
#else
		while (r.tick())
			;
#endif
	} catch (std::exception& e) {
		std::cerr << e.what();
	}
}
