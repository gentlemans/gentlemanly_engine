#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include <memory>

namespace ge
{
class camera_component;
class model_system;
namespace concept
{
template <typename X>
struct Viewport
{
	BOOST_CONCEPT_USAGE(Viewport)
	{
		const X& i_c = i;

		i.set_background_color(glm::vec4{});


	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
