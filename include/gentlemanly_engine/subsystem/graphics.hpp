#pragma once

#include "gentlemanly_engine/concept/subsystem.hpp"

#include <SDL.h>

// this class implements the Subsystem concept define in subsystem.h


namespace ge
{

namespace subsystem
{

struct graphics 
{
	Uint32 get_sdl_init_flags()
	{
		return SDL_INIT_VIDEO;
	}
};

} // namespace subsytem

} // namespace ge

