#include <ge/actor_ticker_subsystem.hpp>
#include <ge/audio_subsystem.hpp>
#include <ge/camera_actor.hpp>
#include <ge/log.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/sound_actor.hpp>

#include <chrono>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

using namespace ge;

struct my_sound_actor : actor {
	sound_actor* m_sound;

	void initialize(const char* asset_path)
	{
		m_sound = factory<sound_actor>(this, asset_path).get();

		add_interface<my_sound_actor, tickable>();

		set_relative_location({-5, -5});

		m_sound->play();
	}

	void tick(std::chrono::duration<float> d)
	{
		set_relative_location(
			{get_relative_location().x, get_relative_location().y + 5 * d.count()});
	}
};

int main()
{
	runtime r;
	r.m_asset_manager.add_asset_path("data/");

	r.add_subsystem<audio_subsystem>({});
	r.add_subsystem<actor_ticker_subsystem>({});

	auto audio_actor = actor::root_factory<my_sound_actor>(&r, "hello.sound");
	r.set_root_actor(audio_actor.get());

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
