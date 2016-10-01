#include <ge/runtime.hpp>
#include <ge/audio_subsystem.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/sound_actor.hpp>
#include <ge/camera_actor.hpp>

using namespace ge;

int main()
{
	runtime r;
	r.m_asset_manager.add_asset_path("data/");
	auto& sdl = r.add_subsystem<sdl_subsystem>({
		"hello ge!",  // title of the window
		{},  // location on the screen, {} for OS defined (it's a boost::optional<glm::uvec2>)
		{720, 1280},  // the size of the window
		false,		  // fullscreen or not
		true		  // if the window should be decorated (border etc).
	});
	r.add_subsystem<audio_subsystem>({});
	
	auto root = actor::root_factory(&r);
	auto camera = actor::factory<camera_actor>(root.get(), 3);
	
	auto audio_actor = actor::factory<sound_actor>(root.get(), "hello.sound");
	audio_actor->play();
	
	sdl.set_root_actor(root.get());
	
	while(r.tick());
}
