#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>
#include <ge/camera_actor.hpp>
#include <ge/input_consumer.hpp>
#include <ge/input_consumer.hpp>
#include <ge/material_asset.hpp>
#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/mesh_asset.hpp>
#include <ge/ui/render_interface.hpp>
#include <ge/ui/rocket_document_asset.hpp>
#include <ge/ui/rocket_font_asset.hpp>
#include <ge/ui/rocket_input_consumer.hpp>
#include <ge/ui/system_interface.hpp>
#include <ge/sdl_application.hpp>

#include <glm/glm.hpp>

#include <memory>

#include "grid.hpp"
#include "zombie.hpp"

using namespace ge;



int main(int argc, char** argv) {
	sdl_application app(argc, argv);
	auto window = app.make_window(
		"gentlemanly_engine_example_opening_window", {}, {1280, 720}, false, true);
	auto viewport = app.make_viewport(*window);

	auto root_actor = actor::factory(nullptr);

	asset_manager asset_man;
	asset_man.add_asset_path("data/");

	
	app.execute(*window);

}
