#pragma once

#include <boost/concept_check.hpp>

#include "ge/actor.hpp"
#include "ge/camera_actor.hpp"
#include "ge/world.hpp"

namespace ge
{
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

		auto my_world = std::make_unique<world>();
		i.set_world(std::move(my_world));

		world& w = i_c.get_world();

		i.set_camera(*(camera_actor*)nullptr);
		camera_actor& cam = i_c.get_camera();
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
