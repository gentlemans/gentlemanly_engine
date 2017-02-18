#include <ge/input_subsystem.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/renderable.hpp>
#include <ge/rocket_document_asset.hpp>
#include <ge/rocket_input_consumer.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/timer_subsystem.hpp>
#include <ge/actor_ticker_subsystem.hpp>

#include <glm/glm.hpp>

#include <cmath>
#include <memory>
#include "grid.hpp"
#include "grid_rocket_element.hpp"
#include "gridtick_interface.hpp"
#include "hud.hpp"
#include "piece.hpp"
#include "spike.hpp"
#include "gridcamera.hpp"
#include "turret.hpp"
#include "wall.hpp"
#include "zombie.hpp"
#include "zombiespawner.hpp"
#include "zombieupgrade.hpp"
#include "beartrap.hpp"

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
	auto& sdl = r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Example!", {640, 960}});
	auto& rocket = r.add_subsystem<rocket_subsystem>({});
	r.add_subsystem<actor_ticker_subsystem>({});

	r.register_interface<renderable>();
	r.register_interface<tickable>();
	r.register_interface<gridtick_interface>();

	auto root = actor::root_factory(&r);

	auto camera = actor::factory<grid_camera>(
		root.get(), 11, sdl.get_aspect_ratio());

	sdl.set_background_color({.2f, .2f, .2f});
	sdl.set_camera(camera.get());
	r.set_root_actor(root.get());

	// initialize the grid
	auto g = actor::factory<grid>(root.get(), glm::ivec2{11, 11}, 20.f);
	actor::factory<zombieupgrade>(g.get(), glm::ivec3(-2, -2, -2));
	actor::factory<wall>(g.get(), glm::ivec2(4, 4));
	actor::factory<wall>(g.get(), glm::ivec2(4, 6));
	actor::factory<wall>(g.get(), glm::ivec2(6, 4));
	actor::factory<wall>(g.get(), glm::ivec2(6, 6));

	actor::factory<spike>(g.get(), glm::ivec2(3, 4));
	actor::factory<spike>(g.get(), glm::ivec2(3, 6));

	actor::factory<turret>(g.get(), glm::ivec2(4, 5), piece::WEST);
	actor::factory<beartrap>(g.get(), glm::ivec2(3, 5));
	actor::factory<turret>(g.get(), glm::ivec2(5, 6), piece::NORTH);
	actor::factory<beartrap>(g.get(), glm::ivec2(5, 7));
	actor::factory<turret>(g.get(), glm::ivec2(6, 5), piece::EAST);
	actor::factory<beartrap>(g.get(), glm::ivec2(7, 5));
	actor::factory<turret>(g.get(), glm::ivec2(5, 4), piece::SOUTH);
	actor::factory<beartrap>(g.get(), glm::ivec2(5, 3));

	for (int x = 0; x < 12; x++) {
		actor::factory<zombiespawner>(g.get(), glm::ivec2(-1, x));
		actor::factory<zombiespawner>(g.get(), glm::ivec2(11, x - 1));
		actor::factory<zombiespawner>(g.get(), glm::ivec2(x - 1, -1));
		actor::factory<zombiespawner>(g.get(), glm::ivec2(x, 11));
	}
	g->try_spawn_z();

	camera->center_piece({ 0, 0 });


// 	Rocket::Debugger::Initialise(rocket.m_context);
// 	Rocket::Debugger::SetVisible(true);


	rocket_input_consumer ic{&r};
	ic.steal_input();

	actor::factory<hud>(root.get(), g.get(), camera.get());

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
