#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include <memory>

namespace ge
{
class actor;
class camera_actor;
class world;
namespace concept
{
template <typename X>
struct Viewport
{
	BOOST_CONCEPT_USAGE(Viewport)
	{
		const X& i_c = i;

		i.set_background_color(glm::vec4{});

		i.render();

		i.set_world(std::unique_ptr<world>{}); 

		world& w = i_c.get_world();

		i.set_camera(*(camera_actor*)nullptr);
		camera_actor& cam = i_c.get_camera();
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
