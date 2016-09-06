#include "ge/rocket_subsystem.hpp"

#include <Rocket/Core.h>

using namespace ge;

bool rocket_subsystem::initialize(rocket_subsystem::config) {
	
	// get asset_manager
	auto asset_man = m_runtime->get_subsystem<asset_manager>();
	if(!asset_man) {
		// TODO: logging
		return false;
	}
	
	auto sdl_sub = m_runtime->get_subsystem<sdl_subsystem>();
	if(!sdl_sub) {
		return false;
	}
	
	auto m_render_interface = new ui::render_interface(*asset_man, *sdl_sub);
	auto m_system_interface = new ui::system_interface(*m_runtime);

	
	Rocket::Core::SetSystemInterface(m_system_interface);
	Rocket::Core::SetRenderInterface(m_render_interface);
	
	Rocket::Core::Initialise();
	
	return true;
}

bool rocket_subsystem::update(std::chrono::duration<float> delta)
{
}


bool rocket_subsystem::shutdown()
{
	return true;
}
