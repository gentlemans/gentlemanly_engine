#pragma once

#include <boost/concept_check.hpp>

#include <glm/glm.hpp>

#include "ge/input_event.hpp"

#include <memory>
#include <vector>

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

		// this should be a Window<>
		auto& win = i_c.get_window();

		std::vector<input_event> ev = i.get_input_events();

		float aspect = i_c.get_aspect_ratio();
	}

private:
	X i;
};

}  // namespace concept

}  // namespace ge
