#pragma once

#include "gentlemanly_engine/concept/subsystem.hpp"

#include <SDL.h>

#include <thread>

// this class implements the Subsystem concept define in subsystem.h
namespace ge
{

namespace subsystem
{

class graphics 
{
public:
	Uint32 get_sdl_init_flags() const
	{
		return SDL_INIT_VIDEO;
	}
	
	void post_init();
};

} // namespace subsytem

// make sure it actually complies with the concept
BOOST_CONCEPT_ASSERT((concept::Subsystem<subsystem::graphics>));

} // namespace ge


