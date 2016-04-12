#pragma once

#include <boost/concept_check.hpp>

#include "ge/actor.hpp"
#include "ge/camera.hpp"

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
		
		i.render_actor(new actor);
		
		i.set_camera(new camera);
		camera* cam = i_c.get_camera();
	}
	
private:
	
	X i;
	const X i_c;
	
	
	
};

} // namespace concept

} // namespace ge
