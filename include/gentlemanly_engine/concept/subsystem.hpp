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
		Uint32 flags{i_c.get_sdl_init_flags()};
		
		i.post_init();
	}
	
private:
	
	X i;
	const X i_c;
};

} // namespace concept

} // namespace ge
