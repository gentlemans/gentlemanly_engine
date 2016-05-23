#include <ge/model_system.hpp>
#include <ge/qt_application.hpp>

#include <ge/asset_manager.hpp> 
#include <ge/material_asset.hpp>
#include <ge/mesh_asset.hpp>
#include <ge/camera_component.hpp>
#include <ge/transform_component.hpp>
#include <ge/world.hpp>

#include <iostream>
#include <memory>



using namespace ge;


int main(int argc, char** argv)
{
	try {
	
		qt_application app(argc, argv);
		auto window = app.make_window("gentlemanly_engine_example_opening_window", {}, {1280, 720}, false, true);
		auto viewport = app.make_viewport(*window);
		
		ge::world world;
		
		asset_manager asset_man;
		asset_man.add_asset_path("data/");
		
		entityx::Entity camera;
		
		app.signal_init.connect([&]{
				
			viewport->set_background_color({1.f, 0.f, 0.f, 1.f});
			
			auto meshasset = asset_man.get_asset<mesh_asset>("square");
			auto wallMesh = asset_man.get_asset<mesh_asset>("ground");
			
			
			
			// wall
			auto wall = world.entities.create();
			wall.assign<model_component>(wallMesh.data);
			wall.assign<transform_component>(transform{{4.f, 0.f}, 3.f});
			
			// init camera
			camera = world.entities.create();
			auto trans = camera.assign<transform_component>(transform{{-0.f, 0.f}, 0.f});
			camera.assign<camera_component>(20.f);
			
		}
		);
		
		app.signal_update.connect([&](float dt){
			world.update(dt);
		}
		);
	
		app.execute(*window);
		
		
	
	} catch (std::exception& e)
	{
		std::cout << e.what();
		return 232;
	}
	
}
