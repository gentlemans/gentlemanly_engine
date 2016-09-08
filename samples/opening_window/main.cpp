#include <ge/asset_manager.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/ui/rocket_document_asset.hpp>

#include <iostream>
#include <memory>

using namespace ge;

int main(int argc, char** argv)
{
	runtime r;
	auto sdl = r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Example!", {}, {1024, 720}});
	auto asset_man = r.add_subsystem<asset_manager>({"data/"});
	r.add_subsystem<rocket_subsystem>({});

	auto root = actor::root_factory(&r);

	auto camera = actor::factory<camera_actor>(root.get(), 10);

	sdl.set_background_color({.2f, .2f, .2f});
	sdl.set_camera(camera.get());
	sdl.set_root_actor(root.get());

	auto document = asset_man.get_asset<ui::rocket_document_asset>("rocket_doc");
	document->Show();

	while (r.tick())
		;
}
