#include <ge/animation_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/input_subsystem.hpp>
#include <ge/texture_asset.hpp>
#include <ge/shader_asset.hpp>
#include <ge/actor_ticker_subsystem.hpp>

using namespace ge;

int main() {

    runtime r;
    r.m_asset_manager.add_asset_path("data/");
    r.add_subsystem<input_subsystem>({});
	r.add_subsystem<actor_ticker_subsystem>({});
    auto& sdl = r.add_subsystem<sdl_subsystem>({
        "Example",
        {},
        {1280, 720}
    });

    auto root_actor = actor::root_factory(&r);
    r.set_root_actor(root_actor.get());

    mesh_settings msettings = r.m_asset_manager.get_asset<mesh_settings_asset>("texturedmodel/textured.meshsettings");
	msettings.m_material.m_shader = r.m_asset_manager.get_asset<shader_asset>("animation.shader");
    msettings.m_material.m_property_values["Texture"] = r.m_asset_manager.get_asset<texture_asset>("animationtest.texture");
	msettings.m_material.m_property_values["dimx"] = 6;
	msettings.m_material.m_property_values["dimy"] = 4;

    auto animation_act = actor::factory<animation_actor>(root_actor.get(), msettings, 40.f);

    auto camera = actor::factory<camera_actor>(root_actor.get(), 4);
    sdl.set_camera(camera.get());

    while(r.tick());
}
