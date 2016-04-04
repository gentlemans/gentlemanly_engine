#pragma once

#include <boost/concept_check.hpp>

#include <SDL.h>

namespace ge
{

namespace concept
{

// the concept for subsystems
template<typename X>
struct Subsystem : boost::DefaultConstructible<X>
{
	BOOST_CONCEPT_USAGE(Subsystem)
	{
		// use brackets to make sure that there is no type conversion
		Uint32 flags{i.get_sdl_init_flags()};
	}
	
private:
	
	X i;
};

} // namespace concept

} // namespace ge
