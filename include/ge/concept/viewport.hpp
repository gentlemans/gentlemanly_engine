#pragma once

#include <boost/concept_check.hpp>

namespace ge
{

namespace concept
{

// the concept for subsystems
template<typename X>
struct Viewport
{
	BOOST_CONCEPT_USAGE(Viewport)
	{
		i.set_background_color(glm::vec4{});
	}
	
private:
	
	X i;
	const X i_c;
};

} // namespace concept

} // namespace ge
