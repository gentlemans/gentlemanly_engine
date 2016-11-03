#include <ge/input_subsystem.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/timer_subsystem.hpp>
#include <ge/rocket_document_asset.hpp>
#include <ge/rocket_input_consumer.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <cmath>
#include "grid.hpp"
#include "piece.hpp"
#include "turret.hpp"
#include "zombie.hpp"

#include <Rocket/Debugger/Debugger.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace ge;

int main()
{
	runtime r;

	r.m_asset_manager.add_asset_path("data/");
	r.add_subsystem<input_subsystem>({});
	r.add_subsystem<timer_subsystem>({});
	auto& sdl = r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Example!", {1024, 720}});
	auto& rocket = r.add_subsystem<rocket_subsystem>({});

	// load UI
	auto doc = r.m_asset_manager.get_asset<rocket_document_asset>("gridui/doc.rocketdocument");
	doc->Show();
	
	auto root = actor::root_factory(&r);

	auto camera = actor::factory<camera_actor>(root.get(), 50);

	sdl.set_background_color({.2f, .2f, .2f});
	sdl.set_camera(camera.get());
	r.set_root_actor(root.get());

	// initialize the grid
	auto g = actor::factory<grid>(root.get(), glm::ivec2{11, 11}, 20000.f);
	actor::factory<zombie>(g.get(), glm::ivec3(1, 1, 2));
	actor::factory<zombie>(g.get(), glm::ivec3(2, 4, 2));
	actor::factory<zombie>(g.get(), glm::ivec3(2, 7, 2));
	actor::factory<turret>(g.get(), glm::ivec3(7, 7, 2));// ->set_relative_rotation(glm::half_pi<float>());
	for (int x = 0; x < 11; x++) {
		actor::factory<turret>(g.get(), glm::ivec3(-1, x, 2));
		actor::factory<turret>(g.get(), glm::ivec3(11, x, 2));
		actor::factory<turret>(g.get(), glm::ivec3(x, -1, 2));
		actor::factory<turret>(g.get(), glm::ivec3(x, 11, 2));
	}
	
//	Rocket::Debugger::Initialise(rocket.m_context);
//	Rocket::Debugger::SetVisible(true);
	
	
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
}
