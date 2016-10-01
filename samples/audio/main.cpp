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

	r.add_subsystem<audio_subsystem>({});
	
	auto audio_actor = actor::root_factory<sound_actor>(&r, "hello.sound");
	audio_actor->play();
	
	while(r.tick());
}
