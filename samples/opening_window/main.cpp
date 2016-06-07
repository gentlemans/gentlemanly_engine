#include <ge/sdl_application.hpp>

#include <ge/actor.hpp>
#include <ge/asset_manager.hpp>
#include <ge/camera_actor.hpp>
#include <ge/input_consumer.hpp>
#include <ge/input_consumer.hpp>
#include <ge/material_asset.hpp>
#include <ge/mesh.hpp>
#include <ge/mesh_actor.hpp>
#include <ge/mesh_asset.hpp>

#include <iostream>
#include <memory>

using namespace ge;

struct wall_actor : actor, input_consumer<wall_actor>
{
	mesh_actor* m_mesh;  // this doesn't need to be a shared_ptr because the actor already tracks it

	void initialize(const std::shared_ptr<mesh>& mesh)
	{
		m_mesh = actor::factory<mesh_actor>(this, mesh).get();

		steal_input();
	}

	void handle_input(const input_event& ev)
	{
		if (ev == input_event{input_keyboard{key::e_w, true}})
		{
			m_mesh->set_relative_location(m_mesh->get_relative_location() + glm::vec2{1.f, 1.f});
		}
		else if (ev == input_event{input_keyboard{key::e_s, true}})
		{
			m_mesh->set_relative_location(m_mesh->get_relative_location() - glm::vec2{1.f, 1.f});
		}
	}
};

int main(int argc, char** argv)
{
	try
	{
		sdl_application app(argc, argv);
		auto window = app.make_window(
			"gentlemanly_engine_example_opening_window", {}, {1280, 720}, false, true);
		auto viewport = app.make_viewport(*window);

		auto root_actor = actor::factory(nullptr);

		asset_manager asset_man;
		asset_man.add_asset_path("data/");

		std::shared_ptr<camera_actor> camera;

		app.signal_init.connect([&] {

			viewport->set_background_color({.2f, .2f, .2f, 1.f});

			auto meshasset = asset_man.get_asset<mesh_asset>("square");
			auto wallMesh = asset_man.get_asset<mesh_asset>("ground");

			// wall
			auto wall = actor::factory<wall_actor>(root_actor.get(), meshasset.data);
			wall->set_relative_location({1.f, 3.f});

			// init camera
			camera = actor::factory<camera_actor>(root_actor.get(), 5.f);

		});

		app.signal_update.connect([&](float dt) {
			camera->render_actors(*root_actor, viewport->get_aspect_ratio());
			input_consumer_manager::process_events(*viewport);
		});

		app.execute(*window);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 232;
	}
}
