#include <ge/actor_ticker_subsystem.hpp>
#include <ge/animation_actor.hpp>
#include <ge/input_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/shader_asset.hpp>
#include <ge/texture_asset.hpp>

using namespace ge;

int main()
{
	// create a runtime object
	runtime r;

	// make sure it can find assets. This will fail if working directory isn't
	// gentlemanly_engine/samples
	r.m_asset_manager.add_asset_path("data/");

	// animations need tick events, so we need the ticker subsystem
	r.add_subsystem<actor_ticker_subsystem>({});

	// create a window
	auto& sdl = r.add_subsystem<sdl_subsystem>({
		"Example",   // title
		{1280, 720}  // size
	});

	// create a root or world actor
	auto root_actor = actor::root_factory(&r);
	r.set_root_actor(root_actor.get());

	// create the animation actor
	auto animation_act = actor::factory<animation_actor>(
		root_actor.get(), "animation/jumpanimation.meshsettings", 40.f);

	// create a camera to see through
	auto camera = actor::factory<camera_actor>(root_actor.get(), 4);
	sdl.set_camera(camera.get());

	// run the engine!
	while (r.tick())
		;
}
