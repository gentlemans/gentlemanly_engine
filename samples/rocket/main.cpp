#include <ge/asset_manager.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/ui/rocket_document_asset.hpp>
#include <ge/ui/rocket_input_consumer.hpp>

#include <iostream>
#include <memory>

using namespace ge;

int main(int argc, char** argv)
{
	runtime r;
	r.m_asset_manager.add_asset_path("data/");
	r.add_subsystem<input_subsystem>({});
	auto& sdl = r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Example!", {}, {1024, 720}});
	auto& rocket = r.add_subsystem<rocket_subsystem>({});

	auto root = actor::root_factory(&r);

	auto camera = actor::factory<camera_actor>(root.get(), 10);

	sdl.set_background_color({.2f, .2f, .2f});
	sdl.set_camera(camera.get());
	sdl.set_root_actor(root.get());

	auto document =
		r.m_asset_manager.get_asset<ui::rocket_document_asset>("rocket/example.rocketdoc");
	document->Show();

	ui::rocket_input_consumer ic{&r};
	ic.steal_input();

	while (r.tick())
		;
}
